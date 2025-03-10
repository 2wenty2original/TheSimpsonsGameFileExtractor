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

	bool HasTripSet = false;
	bool HasTextures = false;
	bool HasGeometryPositions = false;
	bool HasPreLitGeometry = false;
	bool HasGeometryNormals = false;
	bool HasModulatedMaterial = false;
	bool HasTextures2 = false;

	bool HasGeometryLight = false;

	int VertexCount = 0;
	int FaceCount = 0;
	int IndexCount = 0;
	int UnknownCount = 0;


	// i need to make this very clear, this is a terrible way of doing it, im just doing it this way because they all follow the same file format so screw it
	// yes im aware jan this is dumb, i should have a id list and a struct lsit and just go down recursively through the hierachy, this is just easier

	// this is the beginner struct
	Chunk Struct = Chunk(GeometryList.begin(), Offset);

	std::vector<uint8_t> StructSum = Struct.Process(GeometryList, Offset);

	Chunk GeometryListChunk = Chunk(GeometryList.begin(), Offset);


	Chunk GeometryStruct = Chunk(GeometryList.begin(), Offset);


	int GeometryStructSumOffset = 0;
	std::vector<uint8_t> GeometryStructSum = GeometryStruct.Process(GeometryList, Offset);


	// please extract data now


	std::bitset<8> Flags(GeometryStructSum[0]);

	HasTripSet = Flags[0];
	HasGeometryPositions = Flags[1];
	HasTextures = Flags[2];
	HasPreLitGeometry = Flags[3];
	HasGeometryNormals = Flags[4];

	HasGeometryLight = Flags[5];
	HasModulatedMaterial = Flags[6];
	HasTextures2 = Flags[7];

	GeometryStructSumOffset += 2;

	UnknownCount = Char_Byte(GeometryStructSum.begin(), GeometryStructSumOffset, 2).CastToint16_LE().variable;
	FaceCount = Char_Byte(GeometryStructSum.begin(), GeometryStructSumOffset, 4).CastToint32_LE().variable;
	VertexCount = Char_Byte(GeometryStructSum.begin(), GeometryStructSumOffset, 4).CastToint32_LE().variable;


	Chunk MaterialList = Chunk(GeometryList.begin(), Offset);

	Offset += MaterialList.size;

	Chunk ExtensionGeometry = Chunk(GeometryList.begin(), Offset);

	Chunk ExtentsionGeometryStruct = Chunk(GeometryList.begin(), Offset);

	std::vector<uint8_t> GeometruStructOutput = ExtentsionGeometryStruct.Process(GeometryList, Offset);

	int GeometryStructOffset = 0;

	int FaceType = Char_Byte(GeometruStructOutput.begin(), GeometryStructOffset, 4).CastToint32_LE().variable;
	int SplitCount = Char_Byte(GeometruStructOutput.begin(), GeometryStructOffset, 4).CastToint32_LE().variable;
	IndexCount = Char_Byte(GeometruStructOutput.begin(), GeometryStructOffset, 4).CastToint32_LE().variable;

	Chunk Unknown1 = Chunk(GeometryList.begin(), Offset);

	std::vector<uint8_t> Unknwon1Struct = Unknown1.Process(GeometryList, Offset);

	Chunk Unknown2 = Chunk(GeometryList.begin(), Offset);

	std::vector<uint8_t> Unknwon2Struct = Unknown2.Process(GeometryList, Offset);

	Chunk ACTUALGEOMETRY = Chunk(GeometryList.begin(), Offset);


	Geometry = ACTUALGEOMETRY.Process(GeometryList, Offset);

	ConvertToObj(Geometry, VertexCount, FaceCount);

	


}

void FileOpen::ConvertToObj(std::vector<uint8_t> InputData, int VertexCount, int FaceCount) {
	std::ofstream Output("OutputtedModel");
	std::vector<uint8_t> OutputVector;

	int Offset = 0;

	int UselessNumber = Char_Byte(InputData.begin(), Offset, 4).CastToint32_LE().variable;

	int FaceOffset = Char_Byte(InputData.begin(), Offset, 4).CastToint32_LE().variable;

	int MeshDataSize = Char_Byte(InputData.begin(), Offset, 4).CastToint32_LE().variable;

	int MeshChunkStart = Offset;

	Offset += 20;

	int TableCount = Char_Byte(InputData.begin(), Offset, 4).CastToint32_BE().variable;

	int SubTableCount = Char_Byte(InputData.begin(), Offset, 4).CastToint32_BE().variable;



	std::vector<int> DataOffsets;

	for (int i = 0; i < TableCount; i++) {
		Offset += 4;
		DataOffsets.push_back(Char_Byte(InputData.begin(), Offset, 4).CastToint32_BE().variable);
	}

	int DataSubStart = Offset;

	for (int i = 0; i < SubTableCount; i++) {
		Offset += DataSubStart + (i * 0x14);
		int NewOffset = Char_Byte(Geometry.begin(), Offset, 4).CastToint32_BE().variable;
		int Chunkhead = NewOffset + MeshChunkStart + 0xC;

	}

	std::vector<int> Faces;

	for (int i = 0; i < FaceCount; i++) {
		int f = Char_Byte(InputData.begin(), Offset, 2).CastToint16_BE().variable;
		Faces.push_back(f);

	}


	for (int i = 0; i < InputData.size(); i+=3) {
		
	}


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
