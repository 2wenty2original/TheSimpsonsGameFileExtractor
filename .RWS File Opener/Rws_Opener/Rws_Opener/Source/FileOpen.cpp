#include "FileOpen.h"

void FileOpen::Init()
{

	std::ifstream EntireFile;
	std::string Line;

	EntireFile.open(Name.c_str(), std::ios::binary);

	if (!EntireFile.is_open()) {
		std::cerr << "cant open file" << Name.c_str() << "\n";
		EntireFile.close();
		return;
	}

	else {


		while (!EntireFile.eof()) { // loop through whole file

			std::getline(EntireFile, Line);
			ProcessLines(Line, Characters);
		}

		EntireFile.close();

	}
}

void FileOpen::ProcessLines(std::string Line, std::vector<unsigned char>& _Characters)
{
	int Length = Line.size();

	for (int i = 0; i < Length; i++) {
		_Characters.push_back(Line[i]);
		AmountOfCharacters += 1;

	}
}

void FileOpen::ExtractData()
{
	std::vector<int> ChunkIds = { 14, 20, 26 };

	bool FoundGeometry = false;
	bool InChunk = false;
	int Offset = 0;

	int GeometryTypeId = 26;


	// fuck it make this bitch recursive, iknow you can, thsi isnt hard

	while (!FoundGeometry) {
		Chunk GetChunk = Chunk(Characters.begin(), Offset);


		for (int i = 0; i < ChunkIds.size(); i++) {
			if (ChunkIds[i] == GetChunk.type) {
				InChunk = true;
			}
		}



		if (GetChunk.type == GeometryTypeId) {
			FoundGeometry = true;
			GeometryList.insert(GeometryList.begin(), Characters.begin() + Offset, Characters.begin() + Offset + GetChunk.size);

			break;
		}

		else if (GetChunk.type == 16) {
			Chunk StructureCheck = Chunk(Characters.begin(), Offset);

			if (StructureCheck.type == 1) {
				Offset += StructureCheck.size;
			}
		}

		else {
			Offset += GetChunk.size;
			InChunk = false;
		}
	}
}

void FileOpen::ProcessData() {

	int Offset = 0;

	bool HasTextures = false;
	bool HasGeometryPositions = false;
	bool HasPreLitGeometry = false;
	bool HasGeometryNormals = false;

	int VertexCount = 0;
	int FaceCount = 0;


	// this is the beginner struct
	Chunk Struct = Chunk(GeometryList.begin(), Offset);

	std::vector<uint8_t> StructSum = Struct.Process(GeometryList, Offset);

	Chunk GeometryListChunk = Chunk(GeometryList.begin(), Offset);


	Chunk GeometryStruct = Chunk(GeometryList.begin(), Offset);

	std::vector<uint8_t> GeometryStructSum = GeometryStruct.Process(GeometryList, Offset);

	Chunk MaterialList = Chunk(GeometryList.begin(), Offset);

	Offset += MaterialList.size;

	Chunk ExtensionGeometry = Chunk(GeometryList.begin(), Offset);

	Chunk ExtentsionGeometryStruct = Chunk(GeometryList.begin(), Offset);

	std::vector<uint8_t> GeometruStructOutput = ExtentsionGeometryStruct.Process(GeometryList, Offset);


}

void FileOpen::ConvertToObj() {
	std::ofstream Output("OutputtedModel");
	std::vector<uint8_t> OutputVector;





	for (size_t  i = 0; i < Triangles.size(); i++) {

		std::string Line = "v " + std::to_string(Triangles[i][0]) + 
			" " + std::to_string(Triangles[i][1]) + 
			" " + std::to_string(Triangles[i][2]) +
			"\n";

		OutputVector.insert(OutputVector.end(), Line.begin(), Line.end());
		std::cout << Line << std::endl; 
	}

	for (size_t i = 0; i < Indexes.size(); i++) {

		std::string Line = "f " + std::to_string(Indexes[i][0]) + "/" + "0" + "/" + "0" + " " 
			+ std::to_string(Indexes[i][1]) + "/" + "0" + "/" + "0" + " " 
			+ std::to_string(Indexes[i][2]) + "/" + "0" + "/" + "0" + " " + "\n";

			
		OutputVector.insert(OutputVector.end(), Line.begin(), Line.end());
		std::cout << Line << std::endl; 
	}


	if (!Output.is_open()) {
		return;
	}

	if (!OutputVector.empty()) {
		Output.write((const char*)(OutputVector.data()), OutputVector.size());
	}
}
