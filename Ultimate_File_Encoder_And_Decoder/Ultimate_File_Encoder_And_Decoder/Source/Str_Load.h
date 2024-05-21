#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <math.h>
#include <string>
#include <vector>



class Str_Load {

public:

	Str_Load(const char* file);
	~Str_Load() {};


	void init();
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

private:

	char* Filename = nullptr;

	std::vector<unsigned int> DataList;
	std::fstream FileObject;



	std::vector<std::vector<std::string>> ListOfAsciiCharacters;
	std::vector<std::vector<std::string>> ListOfBinaryCharacters;
	std::vector<std::vector<std::string>> ListOfFinals;


	std::vector<std::string> BinaryList;
	std::vector<std::string> AsciiList;
	std::vector<std::string> FinalList;

	int Index;


};
