#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "Bytes.h"
#include <filesystem>


class BSPOpen {
public:
	BSPOpen() {}

	BSPOpen(std::string _name)
	{
		Name = _name;
	}




	void Init();
	void ProcessLines(std::string Line, std::vector<unsigned char>& _Characters);
	void ReadHeader();
	void WriteToFile();



public:

	int GlobalFileIndex = -1;

	std::vector<uint8_t> OutputVector;


	std::string FilePath;



private:
	int GlobalFileOffset;

	std::fstream FileObject;

	std::string Name;

	std::vector<unsigned char> Characters;

	// we can use this as an exit condition
	int ObjectCount = 0;

	int AmountOfCharacters;


	std::vector<uint8_t> Geometry;

	// list of triangles, each sublist will have 3 points

	std::vector < Vector3> Normals;
	std::vector < Vector3> Vertices;
	std::vector < Vector2> UVs;

	std::vector< std::vector<int>> Indexes;




};