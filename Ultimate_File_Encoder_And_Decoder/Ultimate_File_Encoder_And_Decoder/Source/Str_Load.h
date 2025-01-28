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
};

	

static __inline void Init(Scanner *sca, std::vector<uint8_t> *Start, size_t size) {
	sca->Start = Start->begin();
	sca->ptr = Start->begin();
	sca->End = Start->begin() + std::min(size, Start->size());
	sca->overflow = 0;
}

static __inline size_t GetIndex(std::vector<uint8_t>::iterator Start, std::vector<uint8_t>::iterator End) {
	return std::distance(Start, End);
}


static __inline size_t position(Scanner* sca) {
	return (size_t)(sca->ptr - sca->Start);
	//return (size_t)std::distance(sca->ptr, sca->Start);
}

static __inline size_t remaining(Scanner* sca) {
	return (size_t)(sca->End - sca->ptr);
	//return std::distance(sca->ptr, sca->End);
}

static __inline uint8_t overflowed(Scanner* sca) {
	return sca->ptr >= sca->End;
}


static uint8_t read_u8(Scanner* sca) {



	if (sca->End == sca->ptr) {
		sca->overflow = 1;
		return 0;
	}

	uint8_t value = *(sca->ptr++);

	//printf("read_u8: %02X (pos: %zu, remaining: %zu)\n", value, position(sca), remaining(sca));

	return value;
}

static uint16_t read_u16(Scanner* sca) {
	if (remaining(sca) < 2) {
		sca->ptr = sca->End;
		sca->overflow = 1;
		return 0;
	}

	uint16_t x = (uint16_t(sca->ptr[0]) << 8) | sca->ptr[1];  // Ensures proper widening before shifting
	sca->ptr += 2;

	//printf("read_u16: %04X (pos: %zu, remaining: %zu)\n", x, position(sca), remaining(sca));
	return x;
}

static uint32_t read_u24(Scanner* sca) {
	if (remaining(sca) < 3) {
		sca->ptr = sca->End;
		sca->overflow = 1;
		return 0;
	}

	uint32_t x = (uint32_t(sca->ptr[0]) << 16) | (uint32_t(sca->ptr[1]) << 8) | sca->ptr[2];
	sca->ptr += 3;

	//printf("read_u24: %06X (pos: %zu, remaining: %zu)\n", x, position(sca), remaining(sca));
	return x;
}

static void append(Scanner* out, Scanner* in, size_t length)
{
	if (!length) // 15 on this breakpoint
	{
		return;
	}

	/*if (length > 4) {
		length = 4;
	}*/


	// works out remaining bytes, kinda like how vectors work by magnitude this measure displacement

	int inRem = remaining(in);
	int outRem = remaining(out);


	if (remaining(in) < length || remaining(out) < length) {
		if (remaining(in) < length) {
			in->ptr = in->End;
			in->overflow = 1;
			
		}

		if (remaining(out) < length) {
			out->ptr = out->End;
			out->overflow = 1;
			
		}

		return;

	}
	





	// this is like the iterator version of memcpy, i dont like it but its just Source, length and destination

	std::copy_n(in->ptr, length, out->ptr);

	//std::copy_n(in->ptr, length, out->ptr); // 8 on this breakpoint

	//increment iterator

	out->ptr += length;
	in->ptr += length;


}

static void self_copy(Scanner* scanner, size_t distance, size_t length) {
	size_t pos = position(scanner);
	size_t remain = remaining(scanner);


	if (position(scanner) < distance || remaining(scanner) < length) {
		scanner->ptr = scanner->End;
		scanner->overflow = 1;
		return;
	}


	std::vector<uint8_t>::iterator in_ptr = scanner->ptr - distance;
	std::vector<uint8_t>::iterator out_ptr = scanner->ptr;

	//std::copy_n(in_ptr, length, out_ptr);

	for (size_t i = 0; i < length; i++) {
		*out_ptr++ = *in_ptr++;
	}

	scanner->ptr += length;

}



class Str_Load {


	

public:

	Str_Load() {};
	~Str_Load() {};


	void init(const char* file);

	void WriteSectionToFile(std::ofstream& OutFile, std::vector<uint8_t> Data, int index);

	void UnCompressSection(std::vector<char> InData, std::vector<uint8_t>& OutData, size_t InSize, size_t OutSize);
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
