#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "Bytes.h"



class Chunk {

public:

	Chunk() {

	}


	Chunk(std::vector<unsigned char>::iterator Start, int& Offset) {
		type = Char_Byte(Start, Offset, 4).CastToint32_LE().variable;
		size = Char_Byte(Start, Offset, 4).CastToint32_LE().variable;
		version = Char_Byte(Start, Offset, 4).CastToint32_LE().variable;
	}

public:



	unsigned int type = 0;
	unsigned int size = 0;
	long unsigned int version = 0;

};

class FileOpen {

public:

	FileOpen(std::string _name)
	{
		Name = _name;
	}

	


	void Init();
	void ProcessLines(std::string Line, std::vector<unsigned char>& _Characters);
	void ExtractData();
	void ConvertToObj();


private:

	std::fstream FileObject;

	std::string Name;

	std::vector<unsigned char> Characters;

	int AmountOfCharacters;

	int SizeOfFile;
	int FaceAmount;
	int IndexAmount;
	int VertexAmount;

	std::vector<uint8_t> GeometryList;

	// list of triangles, each sublist will have 3 points
	std::vector < std::vector<float>> Triangles;

	std::vector< std::vector<int>> Indexes;

	

	
};