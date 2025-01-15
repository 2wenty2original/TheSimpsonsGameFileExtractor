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



void Str_Load::WriteSectionToFile(std::ofstream& OutFile, std::vector<uint8_t> ByteToWrite, int &index)
{
	if (!OutFile.is_open()) {
		return;
	}

	std::vector<char> InData;

	for (int i = 0; i < ByteToWrite.size(); i ++) {
		char Data = (char)ByteToWrite[i];
		InData.push_back(Data);
	}

	std::string Name = std::to_string(index);

	if (!ByteToWrite.empty()) {
		OutFile.write(InData.data(), ByteToWrite.size());
	}

	index++;
}

void Str_Load::UnCompressSection(Section Sect, std::vector<uint8_t> &Write)
{
	std::vector<uint8_t> InData;

	for (int i = 0; i < Sect.SectionReal.size(); i++) {
		uint8_t Data = (uint8_t)Sect.SectionReal[i];
		InData.push_back(Data);
	}



	Scanner in, out;


	uint8_t Byte_Zero, Byte_One, Byte_Two, Byte_Three;
	uint32_t CompSize, DecompSize;
	uint32_t proc_len, ref_dis, ref_len;

	in.Init(InData);
	out.Init(Write);
	

	while (!in.overflowed() && !out.overflowed())
	{
		Byte_Zero = in.read_u8();

		// 0x80 is for 128, conviniently the size of a signed char  

		if (!(Byte_Zero & 0x80)) {
			Byte_One = in.read_u8();

			proc_len = Byte_Zero & 0x03;

			append(&out, &in, proc_len);

			// opcode/byte command

			ref_dis = ((Byte_Zero & 0x60) << 3) + Byte_One + 1;
			ref_len = ((Byte_Zero >> 2) & 0x07) + 3;

			self_copy(&out, ref_dis, ref_len);
		}

		// 0x40 is for 64, half of a char

		else if (!(Byte_Zero & 0x40)) {
			Byte_One = in.read_u8();
			Byte_Two = in.read_u8();

			proc_len = Byte_One >> 6;
			append(&out, &in, proc_len);

			ref_dis = ((Byte_One & 0x3f) << 8) + Byte_Two + 1;
			ref_len = (Byte_Zero & 0x3f) + 4;
			self_copy(&out, ref_dis, ref_len);
		}

		// 0x20 is for 32, quater of a char

		else if (!(Byte_Zero & 0x20)) {

			Byte_One = in.read_u8();
			Byte_Two = in.read_u8();
			Byte_Three = in.read_u8();

			proc_len = Byte_Zero & 0x03;
			append(&out, &in, proc_len);

			ref_dis = ((Byte_Zero & 0x10) << 12)
				+ (Byte_One << 8) + Byte_Two + 1;
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

		std::vector<uint8_t> WriteTo(SectionList[i].UnCompressedSize.variable);


		UnCompressSection(SectionList[i], WriteTo);



		WriteSectionToFile(TempOutput, WriteTo, index);
		TempOutput.close();
		WriteTo.clear();
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


	int gh = 50;

	

}



bool Str_Load::IsStrFile(std::ifstream& file)
{

	std::string Line;
	std::string SToc = "SToc";
	
	
	//file.open(Filename, std::ios::binary);

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


