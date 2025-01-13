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

//struct Section {
//	int Start;
//	int End;
//	int Size;
//
//};

struct Section {

	// the bytes of the section in header
	std::vector< char>::iterator StartHeader;
	std::vector< char>::iterator EndHeader;

	std::vector< char>::iterator StartReal;
	std::vector< char>::iterator EndReal;


	int Size; // size between Start and End

	int CompressedSize;
	int RealSize;

};

struct Scanner {
	uint8_t *Start;
	uint8_t *ptr;
	uint8_t *End;
	uint8_t overflow;


	void Init(uint8_t *Start, size_t size) {
		this->Start = this->ptr = Start;
		this->End = Start + size;
		this->overflow = 0;
	}
	
};

class Str_Load {


	

public:

	Str_Load() {};
	~Str_Load() {};


	void init(const char* file);

	void UnCompress();

	void ConvertToTxt();
	void ConvertToStr();

	void destroy();

	void IncrementGrid(std::ifstream& _EntireFile);

	void SortGarbeld(std::string CurrentLine);

	void CheckHeaderForCompression();

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


	// name of the file
	char* Filename = nullptr;
	

	// file stream object
	std::fstream FileObject;


	// every single character in the file
	std::vector<char> AllList;


	// used for indexing file
	int Index;


	
	std::vector<Section> SectionList;

	// how many sections there are 
	Uint8_C Sections = 0;


	// start
	Uint8_C StartIndex;
	

	// the size of AllList
	int sizeOfAll = 0; 

	// this contains the 24 byte long sections, obviosuly not the entire real section, but you get the jist
	std::vector<Char_Byte> File_Section_Bytes;

	// This is the hardcoded values for the start of every ACTUAL section
	std::vector<int> StartOfEachFile;


	// the possible Memory policies there even are
	Uint32_C MemPolicyArr[3] = {0x5393AC01, 0x9D6870BC, 0x00000000}; // All possible Memory Policy for memory allocation


	// uncompressed and compressed file size
	unsigned int fileSizeComp = 0;
	unsigned int fileSizeReal = 0;

};
