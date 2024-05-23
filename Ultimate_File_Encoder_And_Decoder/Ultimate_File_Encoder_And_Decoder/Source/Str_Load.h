#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <math.h>
#include <string>
#include <vector>



class Str_Load {

public:

	Str_Load() {};
	~Str_Load() {};


	void init(const char* file);
	void ConvertToTxt(std::vector<std::vector<std::string>> b);
	void ConvertToStr();
	void destroy();

	void Allocate2DVectors();

	std::string GreaterThanLineReturn(float value);
	std::string LessThanLineReturn(float value);

	char GreaterThanInputCharReturn(float value, std::string Line);
	char LessThanInputCharReturn(float value, std::string Line);

	void IncrementGrid(std::ifstream& _EntireFile);

	void SortGarbeld(std::string CurrentLine, int &i);

	std::vector<std::vector<std::string>> ReturnListOfAll() {
		return ListOfAll;
	}

	std::vector<std::vector<std::string>> ReturnListOfBinaryCharacters() {
		return ListOfBinaryCharacters;
	}

	std::vector<std::vector<std::string>> ReturnListOfAsciiCharacters() {
		return ListOfAsciiCharacters;
	}

private:

	char* Filename = nullptr;

	std::vector<unsigned int> DataList;
	std::fstream FileObject;


	std::vector<std::vector<std::string>> ListOfAll;
	std::vector<std::vector<std::string>> ListOfAsciiCharacters;
	std::vector<std::vector<std::string>> ListOfBinaryCharacters;
	


	std::vector<std::string> BinaryList;
	std::vector<std::string> AsciiList;
	std::vector<std::string> AllList;
	

	int Index;


};
