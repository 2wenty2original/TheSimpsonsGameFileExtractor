#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <math.h>
#include <string>
#include <vector>
#include "Bytes.h"



enum MemoryPolic {
	State_1,
	State_2
};

struct PairIndexByte {
	int StartIndex;
	int EndIndex;
};

class Str_Load {


	

public:

	Str_Load() {};
	~Str_Load() {};


	void init(const char* file);

	void UnCompressSection(std::vector<char> SectionOfFile);

	void UnCompress();
	void Compress();

	void ConvertToTxt();
	void ConvertToStr();

	void destroy();




	void IncrementGrid(std::ifstream& _EntireFile);

	void SortGarbeld(std::string CurrentLine);

	void CheckHeaderForCompression();

	void ScanFile();

	bool IsStrFile(std::ifstream &file);

	

	bool IsValidIndex(int index, int Offset, int SizeOfContainer) {
		if ((index + Offset) >= 0 && (index + Offset) < SizeOfContainer) {
			return true;
		}

		else {
			return false;
		}
	}

	

	std::vector<char> ReturnAllList() {
		return AllList;
	}

private:

	char* Filename = nullptr;
	
	std::fstream FileObject;

	std::vector<char> AllList;

	int Index;

	Uint8_C Sections = 0;

	Uint8_C StartIndex;
	
	int sizeOfAll = 0; // size of AllList

	std::vector<Char_Byte> File_Section_Bytes;

	std::vector<int> StartOfEachFile;

	Uint32_C MemPolicyArr[3] = {0x5393AC01, 0x9D6870BC, 0x00000000}; // All possible Memory Policy for memory allocation

	unsigned int fileSizeComp = 0;
	unsigned int fileSizeReal = 0;

};
