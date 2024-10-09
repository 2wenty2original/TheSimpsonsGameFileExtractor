#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "Bytes.h"


class FileOpen {

public:

	FileOpen(std::string _name)
	{
		Name = _name;
	}

	


	void Init();
	void ProcessLines(std::string Line, std::vector<char>& _Characters);
	void DeterminePoints();


private:

	std::fstream FileObject;

	std::string Name;

	std::vector<char> Characters;

	int AmountOfCharacters;

	Uint32_C SizeOfFile;
	Uint32_C FaceAmount;
	Uint32_C IndexAmount;
	Uint32_C VertexAmount;

	

	
};