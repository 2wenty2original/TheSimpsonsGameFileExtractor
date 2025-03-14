#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "Bytes.h"
#include <bitset>



class Vector2 {

public:

	Vector2()
	{
		X = 0;
		Y = 0;

	}
	Vector2(float _X, float _Y, float _Z) : X(_X), Y(_Y) {}

	Vector2 Normalize() {

		float length = std::sqrt(this->X * this->X + this->Y * this->Y);

		if (length != 0) {
			X /= length;
			Y /= length;
		}

		return *this;
	}

	float Dot(const Vector2& Other) {
		return (this->X * Other.X) + (this->Y * Other.Y);
	}



public:

	float X;
	float Y;

	float magnitude;
};



class Vector3 {

public:

	Vector3()
	{
		X = 0;
		Y = 0; 
		Z = 0;

	}
	Vector3(float _X, float _Y, float _Z) : X(_X) , Y(_Y), Z(_Z) {}

	Vector3 Normalize() {

		float length = std::sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);

		if (length != 0) {
			X /= length;
			Y /= length;
			Z /= length;
		}

		return *this;
	}

	float Dot(const Vector3 &Other) {
		return (this->X * Other.X) + (this->Y * Other.Y) + (this->Z * Other.Z);
	}

	Vector3 Cross(const Vector3& Other) const {

		Vector3 Output = Vector3();
		Output.X = this->Y * Other.Z - this->Z * Other.Y;
		Output.Y = this->Z * Other.X - this->X * Other.Z;
		Output.Z = this->X * Other.Y - this->Y * Other.X;

		return Output;
	}


public:

	float X;
	float Y;
	float Z;

	float magnitude;
};


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
	void ConvertToObj(std::vector<uint8_t> InputData, int VertexCount, int FaceCount);
	void ProcessData();

    

	std::vector<std::vector<int>> CastStripToFace(std::vector<int> _Strip) {


		bool Flip = false;
		std::vector<std::vector<int>> Output;

		for (int i = 0; i < _Strip.size() - 2; i++) {
			if (Flip) {
				Output.push_back(std::vector<int>{_Strip[i +2], _Strip[i+1], _Strip[i]});
			}

			else {
				Output.push_back(std::vector<int>{_Strip[i + i], _Strip[i + 2], _Strip[i]});
			}

			Flip = !Flip;
		}


		return Output;
	}




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

	std::vector<uint8_t> Geometry;

	// list of triangles, each sublist will have 3 points
	std::vector < std::vector<float>> Triangles;

	std::vector< std::vector<int>> Indexes;

	

	
};