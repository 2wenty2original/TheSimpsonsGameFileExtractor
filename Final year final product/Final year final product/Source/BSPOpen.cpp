#include "BSPOpen.h"

void BSPOpen::Init()
{
	if (Characters.size() > 0) {
		return;
	}

	std::ifstream EntireFile(Name.c_str(), std::ios::binary | std::ios::ate);
	if (!EntireFile.is_open()) {
		std::cerr << "Cannot open file: " << Name.c_str() << "\n";
		return;
	}


	std::streamsize fileSize = EntireFile.tellg();
	EntireFile.seekg(0, std::ios::beg);

	if (fileSize <= 0) {
		std::cerr << "File size invalid or empty file: " << Name.c_str() << "\n";
		return;
	}

	std::vector<char> buffer(fileSize);

	if (!EntireFile.read(buffer.data(), fileSize)) {
		std::cerr << "Failed to read file content.\n";
		return;
	}

	EntireFile.close();

	for (char ch : buffer) {
		ProcessLines(std::string(1, ch), Characters);
	}

	std::cout << "Completed the Init " << buffer.size() << " Is the Buffer Size\n";
}

void BSPOpen::ProcessLines(std::string Line, std::vector<unsigned char>& _Characters)
{
	int Length = Line.size();

	for (int i = 0; i < Length; i++) {
		_Characters.push_back(Line[i]);
		AmountOfCharacters += 1;

	}
}

void BSPOpen::ReadHeader()
{
	int Offset = 0;

	int Identifier = Char_Byte(Characters.begin(), Offset, 4).CastToint32_BE().variable;
	int BlankNumber = Char_Byte(Characters.begin(), Offset, 4).CastToint32_BE().variable;
	int AmountOfSections = Char_Byte(Characters.begin(), Offset, 4).CastToint32_BE().variable;
	int StartOfSectionsInHeader = Char_Byte(Characters.begin(), Offset, 4).CastToint32_BE().variable;




}

void BSPOpen::WriteToFile()
{

	std::string name("Output");
	name.append(std::to_string(1));
	name.append(".obj");

	std::filesystem::path OutputPath = std::filesystem::path(FilePath) / name;

	std::ofstream Output(OutputPath);




	for (size_t i = 0; i < Vertices.size(); i++) {

		std::string Line = "v " + std::to_string(Vertices[i].X) +
			" " + std::to_string(Vertices[i].Y) +
			" " + std::to_string(Vertices[i].Z) +
			"\n";

		OutputVector.insert(OutputVector.end(), Line.begin(), Line.end());
	}

	for (size_t i = 0; i < UVs.size(); i++) {
		std::string Line = "vt " + std::to_string(UVs[i].X) +
			" " + std::to_string(UVs[i].Y) +
			"\n";

		OutputVector.insert(OutputVector.end(), Line.begin(), Line.end());
	}


	for (size_t i = 0; i < Normals.size(); i++) {
		std::string Line = "vn " + std::to_string(Normals[i].X) +
			" " + std::to_string(Normals[i].Y) +
			" " + std::to_string(Normals[i].Z) +
			"\n";
		OutputVector.insert(OutputVector.end(), Line.begin(), Line.end());
	}

	for (size_t i = 0; i < Indexes.size(); i++) {



		std::string Line = "f " + std::to_string(Indexes[i][0]) + "/" + std::to_string(Indexes[i][0]) + "/" + std::to_string(Indexes[i][0]) + " "
			+ std::to_string(Indexes[i][1]) + "/" + std::to_string(Indexes[i][1]) + "/" + std::to_string(Indexes[i][1]) + " "
			+ std::to_string(Indexes[i][2]) + "/" + std::to_string(Indexes[i][2]) + "/" + std::to_string(Indexes[i][2]) + " " + "\n";


		OutputVector.insert(OutputVector.end(), Line.begin(), Line.end());
	}


	if (!Output.is_open()) {
		return;
	}

	if (!OutputVector.empty()) {
		Output.write((const char*)(OutputVector.data()), OutputVector.size());
	}
}
