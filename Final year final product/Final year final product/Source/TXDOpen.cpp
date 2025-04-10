#include "TXDOpen.h"

void TXDOpen::Init()
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

void TXDOpen::ProcessLines(std::string Line, std::vector<unsigned char>& _Characters)
{
	int Length = Line.size();

	for (int i = 0; i < Length; i++) {
		_Characters.push_back(Line[i]);

	}
}

void TXDOpen::ExtractData()
{

	int HeaderSize = 144;

	int Offset = 0;

	Chunk Clump = Chunk(Characters.begin(), Offset);

	int FileSigComparison = 22;

	if (!(Clump.type == FileSigComparison)) {
		std::cerr << "Error this is not the correct file" << std::endl;
		return;
	}

	// first struct moves offset
	Chunk StartStruct = Chunk(Characters.begin(), Offset);


	// offset is moved by this, DO NOT MOVE IT AGAIN U SWINE
	std::vector<uint8_t> HeaderInfo_1 = StartStruct.Process(Characters, Offset);

	int AmountOfTextures = Char_Byte(HeaderInfo_1.begin(), HeaderInfo_1.begin() + 2).CastToint16_LE().variable;

	int Unknown = Char_Byte(HeaderInfo_1.begin() + 2, HeaderInfo_1.begin() + 4).CastToint16_LE().variable;



	for (int i = 0; i < AmountOfTextures; i++) {
		int LocalOffset = 0;

		Chunk Field = Chunk(Characters.begin(), Offset);


		std::vector<uint8_t> TextureData = Char_Byte(Characters.begin() + Offset, Characters.begin() + Offset + Field.size).Char_Bytes;

		Chunk TextureChunk = Chunk(TextureData.begin(), LocalOffset);

		int Flags = Char_Byte(TextureData.begin(), LocalOffset, 4).CastToint32_LE().variable;

		int FilterFlags = Char_Byte(TextureData.begin(), LocalOffset, 4).CastToint32_LE().variable;

		std::string TextureName(TextureData.begin() + LocalOffset, TextureData.begin() + LocalOffset + 32);

		std::string AlphaName(TextureData.begin() + LocalOffset, TextureData.begin() + LocalOffset + 32);

		LocalOffset += 64;

		int directid = Char_Byte(TextureData.begin(), LocalOffset, 4).CastToint32_BE().variable;

		// this is actually the compression type
		int AlphaFlags = Char_Byte(TextureData.begin(), LocalOffset, 4).CastToint32_BE().variable;

		int Width = Char_Byte(TextureData.begin(), LocalOffset, 2).CastToint16_BE().variable;

		int Height = Char_Byte(TextureData.begin(), LocalOffset, 2).CastToint16_BE().variable;

		int Depth = TextureData[LocalOffset++];

		int mipmap_count = TextureData[LocalOffset++];

		int text_coord_type = TextureData[LocalOffset++];

		int MoreFlags = TextureData[LocalOffset++];

		int Palette = TextureData[LocalOffset++];


		int UnknownEnd = Char_Byte(TextureData.begin(), LocalOffset, 3).CastToint24_BE().variable;

		TextureData.erase(TextureData.begin(), TextureData.begin() + LocalOffset);

		// now its time to convert data
 		ConvertToDDS(TextureData, Width, Height, UnknownEnd, AlphaFlags, mipmap_count, Depth);
		
	}





}

void TXDOpen::ConvertToDDS(std::vector<uint8_t> InputData, int Width, int Height, int LinearNumber, int AlphaFlags, int MinMapCount
	, int Depth)
{

	int HeaderSize = 128;

	std::ofstream Output("Out.dds", std::ios::binary);

	// DDs Signature
	WriteInt(Output, 0x20534444, 4);

	// size of header
	WriteInt(Output, 0x0000007C, 4);


	WriteInt(Output, 0x0002100F, 4);

	WriteInt(Output, Width, 4);

	WriteInt(Output, Height, 4);

	WriteInt(Output, LinearNumber, 4);

	WriteInt(Output, 0x00000001, 4);

	WriteInt(Output, MinMapCount, 4);

	// preallocate 11 bytes

	for (int i = 0; i < 11; i++) {
		WriteInt(Output, 0x00000000, 4);
	}


	// other size
	WriteInt(Output, Depth, 4);

	// flags
	WriteInt(Output, 0x00000041, 4);

	// the fourCC or special characters that denote the directX thingy ( its a magic number basically)
	WriteInt(Output, 0x00000000, 4);

	// RGBBitCount
	WriteInt(Output, 0x00000020, 4);


	// RBitMask
	WriteInt(Output, 0x00FF0000, 4);

	// GBitMask
	WriteInt(Output, 0x0000FF00, 4);

	// BBitMask
	WriteInt(Output, 0x000000FF, 4);

	// BAitMask
	WriteInt(Output, 0xFF000000, 4);

	// Caps 1
	WriteInt(Output, 0x00401008, 4);

	// Caps 2
	WriteInt(Output, 0x00000000, 4);

	// Caps 3
	WriteInt(Output, 0x00000000, 4);

	// Caps 4
	WriteInt(Output, 0x00000000, 4);

	// Reserved 
	WriteInt(Output, 0x00000000, 4);





	// this isnt needed, BUT, if we find a format where we need to swap from rgba to bgra, KEEP THIS
	//for (size_t i = 0; i < InputData.size(); i += 4) {
	//	std::swap(InputData[i], InputData[i + 2]); // Swap R and B
	//}


	// After reorienting, you can now write the data to the .dds file
	if (!Output.is_open()) {
		return;
	}

	Output.write(reinterpret_cast<const char*>(InputData.data()), InputData.size());
	Output.close();

}

void TXDOpen::ConvertToBMP(std::vector<uint8_t> InputData, int Width, int Height, int MimMapCount)
{

	std::ofstream Output("Out.bmp", std::ios::binary);

	// 2 bytes
	WriteInt(Output, 0x4D42, 2);

	// 4 bytes
	WriteInt(Output, 54 + InputData.size(), 4);

	// 2 bytes reserverd
	WriteInt(Output, 0, 2);

	// 2 bytes
	WriteInt(Output, 0, 2);

	// 4 bytes 

	WriteInt(Output, 54,4);



	// DIB header, basically bmp files have 2 headers, its kinda dumnb but thats what the wiki said so whatever

	WriteInt(Output, 40, 4); 

	// width 
	WriteInt(Output, Width, 4);
	//height has to be inverted because its down up
	WriteInt(Output, Height, 4);

	// amount of planes
	WriteInt(Output, 1, 2);

	// pixel depth, 32 is the full set
	WriteInt(Output, 32, 2);

	// compression, might need to change this
	WriteInt(Output, 3, 4);

	// image size, but like physically
	WriteInt(Output, 0, 4);           

	// x pixels per metre
	WriteInt(Output, 0, 4);

	//y pixels per metre
	WriteInt(Output, 0, 4);

	// total colours
	WriteInt(Output, 0, 4);

	//important colours
	WriteInt(Output, 0, 4);   
	
	// this isnt needed, BUT, if we find a format where we need to swap from rgba to bgra, KEEP THIS
	//for (size_t i = 0; i < InputData.size(); i += 4) {
	//	std::swap(InputData[i], InputData[i + 2]); // Swap R and B
	//}

	if (!Output.is_open()) {
		return;
	}

	if (!InputData.empty()) {
		Output.write(reinterpret_cast<const char*>(InputData.data()), InputData.size());
	}

	Output.close();
}

bool TXDOpen::ProcessData(int _ObjectCount)
{
	return false;
}

void TXDOpen::WriteToFile()
{

}
