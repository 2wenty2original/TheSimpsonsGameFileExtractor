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

void Str_Load::UnCompressSection(std::vector<char> SectionOfFile)
{

}

void Str_Load::UnCompress()
{
	std::vector<std::string> FileOutputNames;

	int size = StartOfEachFile.size();

	for (int i = 0; i < size; i++) {
		std::vector<char> Section;

		Section.insert(Section.begin(), );
	}

	std::ofstream OutputFile();

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

		//if (CurrentLine[j] > 33 && CurrentLine[j] < 126) {
		//	//std::string str(1, CurrentLine[j]);
		//	
		//	AllList.push_back(CurrentLine[j]);
		//}

		//else {
		//	//std::string str(1, CurrentLine[j]);
		//	
		//	AllList.push_back(CurrentLine[j]);
		//}
	
	}	
}

		
void Str_Load::CheckHeaderForCompression()
{
	const int InitialOffSet = 20; //where the section part starts
	const int Offset = 24; //how big each section IN THE HEADER is (obviously not size of actual headers)

	sizeOfAll = AllList.size(); // size of the amount of characters
	
	Sections = AllList[8]; // the amount of sections i.e its just a number

	std::vector<char>::iterator StartIndexIterator = AllList.begin() + InitialOffSet;

	for (int i = 0; i < Sections.variable; i++) {

		std::vector<char>::iterator Start = StartIndexIterator + (i * Offset);
		std::vector<char>::iterator End = StartIndexIterator + (i * Offset) + Offset;
		
		Char_Byte StartByte = Char_Byte(Start, End);

		File_Section_Bytes.push_back(StartByte);
	}


	int counter = 0;
	int counter_For_Files = 0;

	int Max = (Sections * Offset).variable + InitialOffSet;

	std::vector<Uint32_C> TempList;

	for (int i = InitialOffSet + 1; i < Max; i++) {
		counter ++;

		if (counter == 24) {
			counter = 0;
		}

		else if (counter == 16) {
			Char_Byte Temp = Char_Byte(AllList.begin() + i, AllList.begin() + i + 4);

			fileSizeComp += Temp.CastToUint32_BE().variable;

			TempList.push_back(Temp.CastToUint32_BE());
			
			
		}

		else if (counter == 8) {
			Char_Byte Temp = Char_Byte(AllList.begin() + i, AllList.begin() + i + 4);
			
			fileSizeReal += Temp.CastToUint32_BE().variable;
			
		}

	}

	int fileStartSize = TempList.size();

	for (int i = 0; i < fileStartSize; i++) {
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






}

void Str_Load::ScanFile()
{
	
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


