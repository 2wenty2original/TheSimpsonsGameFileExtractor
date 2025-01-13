#include "Str_Load.h"



void Str_Load::init(const char* file)
{
	Filename = (char*)file;

	std::ifstream EntireFile;
	std::string line;

	//if (DataList.size() > 0) { DataList.clear(); }

	EntireFile.open(Filename, std::ios::binary);

	if (!EntireFile.is_open()) {
		std::cerr << "cant open file" << Filename << "\n";
		EntireFile.close();
		return;
	}

	else if (IsStrFile(EntireFile) == false) {
		std::cerr << "Not an Str File" << Filename << "\n";
		EntireFile.close();
		return;
	}

	else {

		

		
		IncrementGrid(EntireFile); // takes a file assesses how many lines there are
		EntireFile.open(Filename, std::ios::binary); // open it as a binary file
		

		while (!EntireFile.eof()){ // loop through whole file
			
			
			std::getline(EntireFile, line);
			SortGarbeld(line);
			

			
			
			
			
			

		}

		EntireFile.close();
		



		
		std::cout << "Completed" << std::endl;
	}



	
}



void Str_Load::UnCompress()
{


	Scanner in, out;

	
	uint8_t Byte_Zero, Byte_One, Byte_Two, Byte_Three;

	/*std::vector<char> CurrentSection(AllList.begin() + StartOfEachFile[0], AllList.begin() + StartOfEachFile[0] + StartOfEachFile[1]);*/
	
	while(false)
	{
		

		// 0x80 is for 128, conviniently the size of a signed char  

		if(!(Byte_Zero & 0x80)) {
			std::cout << "hello" << std::endl;
		}

		// 0x40 is for 64, half of a char

		else if (!(Byte_Zero & 0x40)) {

		}

		// 0x20 is for 32, quater of a char

		else if (!(Byte_Zero & 0x20)) {

		}


		// of smaller value

		else {
			uint8_t proc_len = (Byte_Zero & 0x1f) * 4 + 4;
			if (proc_len <= 0x70) 
			{

			}
		}
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
		Char_Byte StartByte = Char_Byte(Start, End);
		File_Section_Bytes.push_back(StartByte);
	}

	std::vector<Uint32_C> TempList;

	for (int i = 0; i < File_Section_Bytes.size(); i++) {

		std::vector<unsigned char> TempCharList;
		TempCharList.insert(TempCharList.begin(), File_Section_Bytes[i].Char_Bytes.begin() + 16, File_Section_Bytes[i].Char_Bytes.begin() + 20);

		Char_Byte CompressedSize = Char_Byte(TempCharList);

		TempList.push_back(CompressedSize.CastToUint32_BE());

	}


	// hard coded locations where the files start, the end via the offset plus the size of the file which is compressed, meaning get the offset, and add its compressed size, to get to where you need to be, assuming of course they are compressed.
	for (int i = 0; i < TempList.size(); i++) {
		int Offset = 2048;
		int Pushed = 0;


		if (i == 0) {
			Pushed += 2048;
		}

		else {
			Pushed += TempList[i - 1].variable + StartOfEachFile[i - 1];
		}

		StartOfEachFile.push_back(Pushed);
	}




	for (int i = 0; i < StartOfEachFile.size(); i++) {

		
		std::vector<char>::iterator Start = AllList.begin() + StartOfEachFile[i];
		std::vector<char>::iterator End = AllList.begin() + StartOfEachFile[i] + StartOfEachFile[i+1];

		int TempSize = abs(StartOfEachFile[i] - StartOfEachFile[i + 1]);

		Section TempSection = Section{Start, End,  };



		SectionList.push_back(TempSection);
	}

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


