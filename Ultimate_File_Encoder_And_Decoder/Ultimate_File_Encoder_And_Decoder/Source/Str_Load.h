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




	void IncrementGrid(std::ifstream& _EntireFile);

	void SortGarbeld(std::string CurrentLine, int &i);

	

	std::vector<char> ReturnAsciiList() {
		return AsciiList;
	}

	std::vector<char> ReturnBinaryList() {
		return BinaryList;
	}

	std::vector<char> ReturnAllList() {
		return AllList;
	}

private:

	char* Filename = nullptr;

	std::vector<unsigned int> DataList;
	std::fstream FileObject;




	std::vector<char> BinaryList;
	std::vector<char> AsciiList;
	std::vector<char> AllList;
	

	int Index;


};
