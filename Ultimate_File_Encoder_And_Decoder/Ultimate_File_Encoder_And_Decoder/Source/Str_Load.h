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
	std::vector<char> SectionHeader;


	// this is the actual section begin and end, the idea being we need to determine these, then apply the decompression algorithm to each, assumign they are compressed, we can determine this mind you via the first 10FB bytes
	std::vector<char> SectionReal;

	// size between Start and End
	int SizeHeader;

	// size between Start and End, real this time tho
	int SizeReal;


	// compressed and real size, this is determine in the header file, the 16th and 8th byte respective of sectioned header
	Uint32_C CompressedSize;
	Uint32_C UnCompressedSize;

};

struct Scanner {
	std::vector<uint8_t>::iterator Start;
	std::vector<uint8_t>::iterator ptr;
	std::vector<uint8_t>::iterator End;
	uint8_t overflow;


	void Init(std::vector<uint8_t>& Data) {
		this->Start = Data.begin();
		this->End = Data.end();
		this->ptr = Data.begin();
		this->overflow = 0;
	}
	


	size_t position() {
		return (size_t)(this->ptr - this->Start);
	}

	size_t remaining() {
		return (size_t)(this->End - this->ptr);
	}

	uint8_t overflowed() {
		return this->overflow;
	}

	uint8_t read_u8() {


		if (this->End == this->ptr) {
			this->overflow = 1;
			return 0;
		}

		

		return *(this->ptr++);
	}

	uint16_t read_u16() {
		uint16_t x;
		if (this->remaining() < 2) {
			this->ptr = this->End, this->overflow = 1;
			return 0;
		}

		x = (this->ptr[0] << 8 | this->ptr[1]);
		this->ptr += 2;
		return x;
	}

	uint32_t read_u24() {
		uint32_t x;
		if (remaining() < 3) {
			this->ptr = this->End, this->overflow = 1;
			return 0;
		}
		x = (this->ptr[0] << 16) | (this->ptr[1] << 8) | this->ptr[2];
		this->ptr += 3;
		return x;
	}



};

class Str_Load {


	

public:

	Str_Load() {};
	~Str_Load() {};


	void init(const char* file);


	

	void WriteSectionToFile(std::ofstream& OutFile, std::vector<uint8_t> ByteToWrite, int &index);

	void UnCompressSection(Section Sect, std::vector<uint8_t> &Write);
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

	static void append(Scanner *out, Scanner *in, size_t length)
	{
		if (!length) 
		{
			return;
		}

		else if (length > 4) {
			length = 4;
		}


		// works out remaining bytes, kinda like how vectors work by magnitude this measure displacement
		if (std::distance(in->ptr, in->End) < static_cast<ptrdiff_t>(length) || 
			std::distance(out->ptr, out->End) < static_cast<ptrdiff_t>(length)) {

			// specifies, determines oveflow
			if (std::distance(in->ptr, in->End) < static_cast<ptrdiff_t>(length)) {
				in->ptr = in->End;
				in->overflow = 1;
				
			}

			// specifies

			if (std::distance(out->ptr, out->End) < static_cast<ptrdiff_t>(length)) {
				out->ptr = out->End;
				out->overflow = 1;
			}

			return;

		}

		// this is like the iterator version of memcpy, i dont like it but its just Source, length and destination


		std::copy_n(in->ptr, length, out->ptr);

		//increment iterator

		out->ptr += length; 
		in->ptr += length;


	}

	void self_copy(Scanner *scanner, size_t distance, size_t length) {



		if (std::distance(scanner->Start, scanner->ptr) < static_cast<ptrdiff_t>(distance) ||
			std::distance(scanner->ptr, scanner->End) < static_cast<ptrdiff_t>(length)) {

			//does overflow

			scanner->ptr = scanner->End;
			scanner->overflow = 1;
			return;
		}

		//in_ptr = scanner->ptr - distance, out_ptr = scanner->ptr;

		auto in_ptr = scanner->ptr - distance;
		auto out_ptr = scanner->ptr;
		
		for (size_t i = 0; i < length; i++) {
			*out_ptr = *in_ptr;
			++out_ptr;
			++in_ptr;

			
		}

		scanner->ptr += length;
	
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
