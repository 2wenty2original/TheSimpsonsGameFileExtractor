#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <math.h>
#include <string>
#include <vector>
#include "Bytes.h"






class Str_Load {



public:




	Str_Load() {};
	~Str_Load() {};


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
	void SortGarbeld(std::string CurrentLine, std::vector<uint8_t>& Output);

	void CheckHeaderForCompression();

	bool IsStrFile(std::ifstream& file);

	std::string StringIndexes(std::string _string, int &index) {
		std::string output;

		for (int i = 0; i < _string.size(); i++) {
			if(_string[i] == 46) {
				output.insert(output.begin(), _string.begin(), _string.begin() + i);
				_string.erase(_string.begin(), _string.begin() + i);
				output.append(std::to_string(index++));
				output.insert(output.end(), _string.begin(), _string.end());

				return output;
			}
		}

	
		return output;
		
	}

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


public:

	std::vector<uint8_t> FileOutput;

	std::string USFP; // uncompressed section folder path
	std::string ExtractedSection; // individual file folder path


private:

	int TextureIndex = 0;
	int ObjectIndex = 0;

	// name of the file
	char* Filename = nullptr;

	
	// file stream object
	std::fstream FileObject;

	// every single character in the file
	std::vector<char> AllList;

	std::vector<Section> SectionList;

	std::vector<std::string> FileNames;

	

	// how many sections there are 
	Uint8_C Sections = 0;
	// the possible Memory policies there even are
	//Uint32_C MemPolicyArr[3] = {0x5393AC01, 0x9D6870BC, 0x00000000}; // All possible Memory Policy for memory allocation
};
