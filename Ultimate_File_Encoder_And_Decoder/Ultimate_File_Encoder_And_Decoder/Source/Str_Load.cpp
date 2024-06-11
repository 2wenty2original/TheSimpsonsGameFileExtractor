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

	else {

		int CurrentIndex = 0; // Index for line
		IncrementGrid(EntireFile); // takes a file assesses how many lines there are
		EntireFile.open(Filename, std::ios::binary); // open it as a binary file
		//Allocate2DVectors(); // initilizes vectors

		while (!EntireFile.eof()){ // loop through whole file
			
			
			std::getline(EntireFile, line);
			SortGarbeld(line, CurrentIndex);
			

			
			
			
			
			

		}

		EntireFile.close();
		



		//ConvertToTxt(ListOfBinaryCharacters);
		std::cout << "Completed" << std::endl;
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

		else {
			Index;
		}
	}

	_EntireFile.close();
}

void Str_Load::SortGarbeld(std::string CurrentLine, int &i) {	

	int Size = CurrentLine.size();

	/*for (int j = 0; j < Size; j++) {
		if (CurrentLine[j] > 33 && CurrentLine[j] < 126) {
			std::string PushString = { CurrentLine[j] };
			std::string FillerString = { "SV" };
			ListOfAsciiCharacters[i].push_back(PushString);
			ListOfBinaryCharacters[i].push_back(FillerString);
			ListOfAll[i].push_back(PushString);
			
			std::string str(1, CurrentLine[j]);
			AllList.push_back(str);
				
		}

		else {
			std::string PushString = { CurrentLine[j] };
			std::string FillerString = { "SV" };
			ListOfAsciiCharacters[i].push_back(FillerString);
			ListOfBinaryCharacters[i].push_back(PushString);
			ListOfAll[i].push_back(PushString);
			
			std::string str(1, CurrentLine[j]);
			AllList.push_back(str);
			
		}
	}*/

	//i += 1;
	
	for (int j = 0; j < Size; j++) {
		if (CurrentLine[j] > 33 && CurrentLine[j] < 126) {
			//std::string str(1, CurrentLine[j]);
			AsciiList.push_back(CurrentLine[j]);
			AllList.push_back(CurrentLine[j]);
		}

		else {
			//std::string str(1, CurrentLine[j]);
			BinaryList.push_back(CurrentLine[j]);
			AllList.push_back(CurrentLine[j]);
		}
	}
}

void Str_Load::ConvertToTxt()
{

	for (int i = 0; i < AllList.size(); i++) {
		if (AllList[i] < 33) {
			//std::cout << b[i][j][w] * 2 << std::endl;
		}
	}


}

void Str_Load::ConvertToStr()
{

}

void Str_Load::destroy()
{

}


