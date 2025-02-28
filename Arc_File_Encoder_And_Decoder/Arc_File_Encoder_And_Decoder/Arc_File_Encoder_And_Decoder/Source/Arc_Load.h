#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <math.h>
#include <string>
#include <vector>
#include "Bytes.h"





class Section {

public:

	Section(){}

	Section(std::vector<uint8_t> *Data, int &_Offset) {
		BitWiseFlag = Char_Byte(Data->begin(), _Offset, 4).CastToint32_BE().variable;
		Offset = Char_Byte(Data->begin(), _Offset, 4).CastToint32_BE().variable;
		Length = Char_Byte(Data->begin(), _Offset, 4).CastToint32_BE().variable;
		UncompressedSize = Char_Byte(Data->begin(), _Offset, 4).CastToint32_BE().variable;
		File = Data;
	}

public:

	unsigned int BitWiseFlag;
	unsigned int Offset;
	unsigned int Length;
	unsigned int UncompressedSize;

	std::vector<uint8_t> *File;




};


class Directory {

public:
	Directory() {

	}

	Directory(int _index, std::vector<uint8_t> *Data, bool IsRoot = false) {

	}

public:

	int Index = 0;
	std::string Name;
	std::string Path;
	std::vector<uint8_t>* Data;

};





class Arc_Load {


	

public:

	Arc_Load() {};
	~Arc_Load() {};


	void init(const char* file);

	void WriteSectionToFile(std::ofstream& OutFile, std::vector<uint8_t> Data, int index);
	void WriteSectionToFile(std::ofstream& OutFile, std::vector<uint8_t> Data);

	void UnCompressSection(std::vector<char> InData, std::vector<uint8_t>& OutData, size_t InSize, size_t OutSize);
	void UnCompress();



	void ExtractSection(const char* Filename);
	void ExtractFiles();

	void ConvertToTxt();
	void ConvertToStr();

	void destroy();

	void SortGarbeld(std::string CurrentLine);
	void SortGarbeld(std::string CurrentLine, std::vector<uint8_t> &Output);

	void CheckHeader();

	bool IsArcFile(std::ifstream &file);

	

	bool IsValidIndex(int index, int Offset, int SizeOfContainer) {
		if ((index + Offset) >= 0 && (index + Offset) < SizeOfContainer) {
			return true;
		}

		else {
			return false;
		}
	}

	

	std::vector<uint8_t> ReturnAllList() {
		return AllList;
	}

private:

	// name of the file
	char* Filename = nullptr;

	std::string USFP; // uncompressed section folder path
	std::string ExtractedSection; // individual file folder path

	// file stream object
	std::fstream FileObject;

	// every single character in the file
	std::vector<uint8_t> AllList;

	std::vector<Section> SectionList;

	std::vector<std::string> FileNames;

	// how many sections there are 
	Uint8_C Sections = 0;
	// the possible Memory policies there even are
	//Uint32_C MemPolicyArr[3] = {0x5393AC01, 0x9D6870BC, 0x00000000}; // All possible Memory Policy for memory allocation
};
