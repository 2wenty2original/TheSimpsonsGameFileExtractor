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

void FileOpen::ProcessLines(std::string Line, std::vector<char>& _Characters)
{
	int Length = Line.size();

	for (int i = 0; i < Length; i++) {

		
		_Characters.push_back(Line[i]);
		AmountOfCharacters += 1;
		

	}

	
}

void FileOpen::DeterminePoints()
{

	// Begin Header

	SizeOfFile = Characters[4];



	// 170 section

	std::vector<char> SelectionOfFile;



	int SourceStart = 0x170; // hard coded value to go to
	int Length = 40; // 40 bytes
	


	SelectionOfFile.resize(Length);
	
	std::memcpy(SelectionOfFile.data(), Characters.data() + SourceStart, Length);


	Char_Byte FaceAmountTemp = Char_Byte(SelectionOfFile.begin() + 4, SelectionOfFile.begin() + 4 + 4);
	Char_Byte VertexAmountTemp = Char_Byte(SelectionOfFile.begin() + 8, SelectionOfFile.begin() + 8 + 4);

	FaceAmount = FaceAmountTemp.CastToUint32_LE();// the 5th index of the 40 byte chunk is faces
	VertexAmount = VertexAmountTemp.CastToUint32_LE(); // the 9th index of the 40 byte chunk is the vertex amount

	SelectionOfFile.clear();

	// 2C0 section defuncted

	

	for (int i = SourceStart; i < Characters.size(); i++) {
		//Char_Byte LocateStruct = Char_Byte(Characters.begin() + i, Characters.begin() + i + 8);
		std::vector<char> g = { 1,0,0,0,1,0,0,0 };

		Char_Byte f = Char_Byte(g.begin(), g.end());

		Uint64_C Check64 = f.CastToUint64_LE();
		if (Check64.variable == 4294967297) {
			int i = 0;
		}
	}

	SourceStart = 0x2C0;
	Length = 20;


	SelectionOfFile.resize(Length);

	std::memcpy(SelectionOfFile.data(), Characters.data() + SourceStart, Length);

	
	Char_Byte IndexAmountTemp = Char_Byte(SelectionOfFile.begin() + 8, SelectionOfFile.begin() + 8 + 4);

	IndexAmount = IndexAmountTemp.CastToUint32_LE();

	int t = 0x324;


}
