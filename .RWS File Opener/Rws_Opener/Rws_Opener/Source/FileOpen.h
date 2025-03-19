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


	Chunk(std::vector<unsigned char>::iterator Start, int& _Offset) {

		Offset = &_Offset;

		type = Char_Byte(Start, _Offset, 4).CastToint32_LE().variable;
		size = Char_Byte(Start, _Offset, 4).CastToint32_LE().variable;
		version = Char_Byte(Start, _Offset, 4).CastToint32_LE().variable;
	}

	std::vector<uint8_t> Process(std::vector<uint8_t> &Data, int &_Offset) {

		std::vector<uint8_t> Output;

		

		if (type == 1 || type == 1294 || type == 59926 || type == 59925 || type == 59955) {
			Output.insert(Output.begin(), Data.begin() + *Offset, Data.begin() + *Offset + size);
			*Offset += size;
		    return Output;
		}



		return Output;
	}

	static int GetIndex(std::vector<uint8_t> List, uint8_t value) {

		auto iterator = std::find(List.begin(), List.end(), value);

		return std::distance(List.begin(), iterator);
	}

	static int GetChunkedIndex(std::vector<uint8_t> List, uint32_t value) {
		for (size_t i = 0; i < List.size() - 3; i++) {
			uint32_t currentValue = (static_cast<uint32_t>(List[i]) << 24) |
				(static_cast<uint32_t>(List[i + 1]) << 16) |
				(static_cast<uint32_t>(List[i + 2]) << 8) |
				static_cast<uint32_t>(List[i + 3]);


			if (currentValue == value) {
				return i; 
			}
		}

		return -1;
	}

public:

	// we can get a pointer to our offset, instead of containing a new one each time
	int* Offset;
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
	void ConvertToObj(std::vector<uint8_t> InputData, int VertexCount, int FaceCount, int _Offset);
	void ProcessData();

    

	std::vector<std::vector<int>> CastStripToFace(std::vector<int> _Strip) {


		bool Flip = false;
		std::vector<std::vector<int>> Output;

		for (int i = 0; i < _Strip.size() - 2; i++) {
			if (Flip) {
				Output.push_back(std::vector<int>{_Strip[i +2], _Strip[i+1], _Strip[i]});
			}

			else {
				Output.push_back(std::vector<int>{_Strip[i + 1], _Strip[i + 2], _Strip[i]});
			}

			Flip = !Flip;
		}


		return Output;
	}




private:

	int GlobalFileOffset;

	std::fstream FileObject;

	std::string Name;

	std::vector<unsigned char> Characters;

	int AmountOfCharacters;

	int SizeOfFile;
	int FaceAmount;
	int IndexAmount;
	int VertexAmount;

	std::vector<uint8_t> GeometryList;

	std::vector<uint8_t> Geometry;

	// list of triangles, each sublist will have 3 points

	std::vector < Vector3> Normals;
	std::vector < Vector3> Triangles;
	std::vector < Vector2> UVs;

	std::vector< std::vector<int>> Indexes;

	

	
};