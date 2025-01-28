#include "Str_Load.h"



void Str_Load::init(const char* file)
{
	Filename = (char*)file;

	std::ifstream EntireFile(Filename, std::ios::binary | std::ios::ate);
	if (!EntireFile.is_open()) {
		std::cerr << "Cannot open file: " << Filename << "\n";
		return;
	}


	std::streamsize fileSize = EntireFile.tellg();
	EntireFile.seekg(0, std::ios::beg);

	if (fileSize <= 0) {
		std::cerr << "File size invalid or empty file: " << Filename << "\n";
		return;
	}

	std::vector<char> buffer(fileSize);

	if (!EntireFile.read(buffer.data(), fileSize)) {
		std::cerr << "Failed to read file content.\n";
		return;
	}

	EntireFile.close();

	for (char ch : buffer) {
		SortGarbeld(std::string(1, ch));  
	}

std::cout << "Completed the Init " << buffer.size() << " Is the Buffer Size\n";

}



void Str_Load::WriteSectionToFile(std::ofstream& OutFile, std::vector<uint8_t> Data, int index)
{
	if (!OutFile.is_open()) {
		return;
	}

	std::string Name = std::to_string(index);

	if (!Data.empty()) {
		OutFile.write((const char*)(Data.data()), Data.size());
	}
}

void Str_Load::UnCompressSection(std::vector<char> InData,std::vector<uint8_t> &OutData, size_t InSize, size_t OutSize)
{
	Scanner in, out;

	uint16_t sig;
	uint8_t Byte_Zero, Byte_One, Byte_Two, Byte_Three;
	uint32_t CompSize, DecompSize;
	uint32_t proc_len, ref_dis, ref_len;


	//std::vector<uint8_t> InDataReal;

	/*for (int i = 0; i < InData.size(); i++) {
		InDataReal.push_back((uint8_t) InData[i]);
	}*/


	Init(&in, reinterpret_cast<std::vector<uint8_t>*>(&InData), InSize);
	Init(&out, &OutData, OutSize);


	sig = read_u16(&in);

	CompSize = (sig & 0x0100) ? read_u24(&in) : 0;

	DecompSize = read_u24(&in);


	while (!overflowed(&in) && !overflowed(&out))
	{
		Byte_Zero = read_u8(&in);

		// 0x80 is for 128, conviniently the size of a signed char  

		if (!(Byte_Zero & 0x80)) {

	

			Byte_One = read_u8(&in);

			proc_len = Byte_Zero & 0x03;
			append(&out, &in, proc_len);

			ref_dis = ((Byte_Zero & 0x60) << 3) + Byte_One + 1;
			ref_len = ((Byte_Zero >> 2) & 0x07) + 3;

			self_copy(&out, ref_dis, ref_len);
		}

		// 0x40 is for 64, half of a char

		else if (!(Byte_Zero & 0x40)) {




			Byte_One = read_u8(&in);
			Byte_Two = read_u8(&in);

			proc_len = Byte_One >> 6;
			append(&out, &in, proc_len);

			ref_dis = ((Byte_One & 0x3f) << 8) + Byte_Two + 1;
			ref_len = (Byte_Zero & 0x3f) + 4;
			self_copy(&out, ref_dis, ref_len);
		}

		// 0x20 is for 32, quater of a char

		else if (!(Byte_Zero & 0x20)) {


			Byte_One = read_u8(&in);
			Byte_Two = read_u8(&in);
			Byte_Three = read_u8(&in);

			proc_len = Byte_Zero & 0x03;
			append(&out, &in, proc_len);

			ref_dis = ((Byte_Zero & 0x10) << 12) + (Byte_One << 8) + Byte_Two + 1;
			ref_len = ((Byte_Zero & 0x0c) << 6) + Byte_Three + 5;
			self_copy(&out, ref_dis, ref_len);

		}




		else {



			proc_len = (Byte_Zero & 0x1f) * 4 + 4;

			if (proc_len <= 0x70) {
				append(&out, &in, proc_len);
			}
			 
			else {
				proc_len = Byte_Zero & 0x3;
				append(&out, &in, proc_len);
				break;  
			}
		}
	}
}

void Str_Load::UnCompress()
{
	int index = 0;
	
	

	for (int i = 0; i < SectionList.size(); i++) {

		std::string name = std::to_string(index);

		std::ofstream TempOutput(name, std::ios::binary);

		std::vector<char> InData = SectionList[i].SectionReal;
		std::vector<uint8_t> OutData(SectionList[i].UnCompressedSize.variable);

		size_t InSize = (size_t)InData.size();
		size_t OutSize = (size_t)OutData.size();

		if (SectionList[i].CompressedSize.variable >= SectionList[i].UnCompressedSize.variable) {
			WriteSectionToFile(TempOutput, std::vector<uint8_t>(InData.begin(), InData.end()), index);
		}

		else {

			UnCompressSection(InData, OutData, InSize, OutSize);
		}


		WriteSectionToFile(TempOutput, OutData, index);

		TempOutput.close();

		index++;

		printf("\n");
	}
}



void Str_Load::IncrementGrid(std::ifstream& _EntireFile)
{
	std::string _line;
	while (!_EntireFile.eof()) {
		std::getline(_EntireFile, _line);

		if (_line.size() > 0) {
			Index += 1;
		}
	}

	_EntireFile.close();
}

void Str_Load::SortGarbeld(std::string CurrentLine) {	

	int Size = CurrentLine.size();

	for (int j = 0; j < Size; j++) {

		AllList.push_back(CurrentLine[j]);

	
	
	}	
}

		
void Str_Load::CheckHeaderForCompression()
{
	const int InitialOffSet = 20; //where the section part starts
	const int Offset = 24; //how big each section IN THE HEADER is (obviously not size of actual headers)

	sizeOfAll = AllList.size(); // size of the amount of characters
	
	Sections = AllList[8]; // the amount of sections i.e its just a number

	std::vector<char>::iterator StartIndexIterator = AllList.begin() + InitialOffSet;


	// this compiles a list of all of the header section file, 24 bytes each respective
	for (int i = 0; i < Sections.variable; i++) {

		std::vector<char>::iterator Start = StartIndexIterator + (i * Offset);
		std::vector<char>::iterator End = StartIndexIterator + (i * Offset) + Offset;


		Section SectionSlice = Section{};

		SectionSlice.SectionHeader.insert(SectionSlice.SectionHeader.begin(), Start, End);
		SectionSlice.SizeHeader = 24;

		SectionList.push_back(SectionSlice);
	}

	int Capacity = AllList.capacity();
	int Size = AllList.size();

	for (int i = 0; i < SectionList.size(); i++) 
	{
		
	
		

		Char_Byte CompressedSize = Char_Byte(SectionList[i].SectionHeader.begin() + 16, SectionList[i].SectionHeader.begin() + 20);

		Char_Byte UnCompressedSize = Char_Byte(SectionList[i].SectionHeader.begin() + 8, SectionList[i].SectionHeader.begin() + 12);



		SectionList[i].CompressedSize = CompressedSize.CastToUint32_BE();
		SectionList[i].UnCompressedSize = UnCompressedSize.CastToUint32_BE();
		

	}



	// hard coded locations where the files start, the end via the offset plus the size of the file which is compressed, meaning get the offset, and add its compressed size, to get to where you need to be, assuming of course they are compressed.

	int Pushed = 2048;

	for (int i = 0; i < SectionList.size(); i++) {
		
		int Start = Pushed;
		
	    Pushed += SectionList[i].CompressedSize.variable;

		int End = Pushed;

	    SectionList[i].SectionReal.insert(SectionList[i].SectionReal.begin(), AllList.begin() + Start, AllList.begin() + End);
		
	}
}



bool Str_Load::IsStrFile(std::ifstream& file)
{

	std::string Line;
	std::string SToc = "SToc";

	std::getline(file, Line);

	if (Line.compare(SToc) == 1) {
		file.close();
		return true;
	}

	else {
		file.close();
		return false;
	}

	return false;
}

void Str_Load::ConvertToTxt()
{

}

void Str_Load::ConvertToStr()
{

}

void Str_Load::destroy()
{

}


