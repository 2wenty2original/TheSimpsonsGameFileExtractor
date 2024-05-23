#include "Str_Load.h"



void Str_Load::init(const char* file)
{
	Filename = (char*)file;

	std::ifstream EntireFile;
	std::string line;

	if (DataList.size() > 0) { DataList.clear(); }

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
		Allocate2DVectors(); // initilizes vectors

		while (!EntireFile.eof()){ // loop through whole file
			
			
			std::getline(EntireFile, line);
			SortGarbeld(line, CurrentIndex);

			
			
			
			
			

		}

		EntireFile.close();
		



		//ConvertToTxt(ListOfBinaryCharacters);
		std::cout << "Completed" << std::endl;
	}



	
}



void Str_Load::Allocate2DVectors() {
	ListOfAsciiCharacters.resize(Index, std::vector<std::string>(0));
	ListOfBinaryCharacters.resize(Index, std::vector<std::string>(0));
	ListOfAll.resize(Index, std::vector<std::string>(0));
}

std::string Str_Load::GreaterThanLineReturn(float value)
{
	for (int i = 0; i < ListOfBinaryCharacters.size(); i++) {
		for (int j = 0; j < ListOfBinaryCharacters[i].size(); j++) {
			for (int w = 0; w < ListOfBinaryCharacters[i][j].size(); w++) {
				if (ListOfBinaryCharacters[i][j][w] < value) {
					return ListOfBinaryCharacters[i][j];
				}
			}
			
		}
	}
}

std::string Str_Load::LessThanLineReturn(float value)
{
	for (int i = 0; i < ListOfBinaryCharacters.size(); i++) {
		for (int j = 0; j < ListOfBinaryCharacters[i].size(); j++) {
			for (int w = 0; w < ListOfBinaryCharacters[i][j].size(); w++) {
				if (ListOfBinaryCharacters[i][j][w] > value) {
					return ListOfBinaryCharacters[i][j];
				}
			}

		}
	}
}

char Str_Load::GreaterThanInputCharReturn(float value, std::string Line)
{
	for (int i = 0; i < Line.size(); i++) {
		if (Line[i] < value) {
			return Line[i];
		}
	}
	
}

char Str_Load::LessThanInputCharReturn(float value, std::string Line)
{
	for (int i = 0; i < Line.size(); i++) {
		if (Line[i] < value) {
			return Line[i];
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

		else {
			Index;
		}
	}

	_EntireFile.close();
}

void Str_Load::SortGarbeld(std::string CurrentLine, int &i) {	
	for (int j = 0; j < CurrentLine.size(); j++) {
		if (CurrentLine[j] > 33 && CurrentLine[j] < 126) {
			std::string PushString = { CurrentLine[j] };
			std::string FillerString = { "SV" };
			ListOfAsciiCharacters[i].push_back(PushString);
			ListOfBinaryCharacters[i].push_back(FillerString);
			ListOfAll[i].push_back(PushString);
				
		}

		else {
			std::string PushString = { CurrentLine[j] };
			std::string FillerString = { "SV" };
			ListOfAsciiCharacters[i].push_back(FillerString);
			ListOfBinaryCharacters[i].push_back(PushString);
			ListOfAll[i].push_back(PushString);
		}
	}

	i += 1;	
}

void Str_Load::ConvertToTxt(std::vector<std::vector<std::string>> b)
{

	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b[i].size(); j++) {
			for (int w = 0; w < b[i][j].size(); w++) {
				if (b[i][j][w] > 0 && b[i][j][w] < 33) {
					//std::cout << b[i][j][w] * 2 << std::endl;
				}

			}
			
		}
	}


}

void Str_Load::ConvertToStr()
{

}

void Str_Load::destroy()
{

}


