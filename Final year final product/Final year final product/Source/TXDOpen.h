#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "Bytes.h"
#include <filesystem>



class TXDOpen {

public:

	TXDOpen(){}

	TXDOpen(std::string _Name) {
		Name = _Name;
	}

	~TXDOpen() {};

	
	// this reads the file as binary and does process lines, needs to be called first
	void Init();

	// this loads the entire file into memory

	void ProcessLines(std::string Line, std::vector<unsigned char>& _Characters);

	// this will get us the geometry section of .rws, mind you not the ACTUAL geometry, thats later, but the chunk
	void ExtractData();

	//this is to add to our global output vector
	void ConvertToDDS(std::vector<uint8_t> InputData, int Width, int Height, int LinerNumber, int AlphaFlags, int MimMapCount, 
		int Depth);

	//this is to add to our global output vector
	void ConvertToBMP(std::vector<uint8_t> InputData, int Width, int Height, int MimMapCount);

	//this is to get us to the actual geometry of the .rws file
	bool ProcessData(int _ObjectCount);

	void WriteToFile();


public:


	std::vector<int> OutputVector;

	std::string FilePath;

	// the whole purpose of this, is to make it impossible to have repeating files, no matter what
	int GlobalFileIndex = -1;

private:

	// this is a really cool methid, basically it breaks down bytes based on their size and converts the sections
	// i.e the hex bytes to uint8_t
	// this is really cool for specific integer sizes for files
	void WriteInt(std::ofstream& out, int value, int byteCount) {
		for (int i = 0; i < byteCount; ++i) {
			uint8_t byte = (value >> (i * 8)) & 0xFF;
			out.write(reinterpret_cast<char*>(&byte), 1);
		}
	}

private:

	int GlobalFileOffset;

	std::fstream FileObject;

	std::string Name;

	std::vector<unsigned char> Characters;
};