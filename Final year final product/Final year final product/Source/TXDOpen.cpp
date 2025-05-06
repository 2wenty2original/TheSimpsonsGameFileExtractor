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

		Offset += TextureData.size();

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

		int Palette = TextureData[Depth == 8 ? 256 * 4 : 0];

		/*LocalOffset++;*/

		// this is basically the size of the texture, the rest are mip maps, can be used for relative offset
		int SizeOfInitialMip = Char_Byte(TextureData.begin(), LocalOffset, 4).CastToUint32_LE().variable;

		TextureData.erase(TextureData.begin(), TextureData.begin() + LocalOffset);




		

		// Output the value in binary to visualize
		std::cout << "Value in binary: " << std::bitset<32>(AlphaFlags) << std::endl;

		// Extract individual bits using bitwise operations
		bool bit_0 = (AlphaFlags & 0x1) != 0;     // 1st bit
		bool bit_1 = (AlphaFlags & 0x2) != 0;     // 2nd bit
		bool bit_2 = (AlphaFlags & 0x4) != 0;     // 3rd bit
		bool bit_3 = (AlphaFlags & 0x8) != 0;     // 4th bit

		bool bit_4 = (AlphaFlags & 0x10) != 0;    // 5th bit
		bool bit_5 = (AlphaFlags & 0x20) != 0;    // 6th bit
		bool bit_6 = (AlphaFlags & 0x40) != 0;    // 7th bit
		bool bit_7 = (AlphaFlags & 0x80) != 0;    // 8th bit

		bool bit_8 = (AlphaFlags & 0x100) != 0;   // 9th bit
		bool bit_9 = (AlphaFlags & 0x200) != 0;   // 10th bit
		bool bit_10 = (AlphaFlags & 0x400) != 0;  // 11th bit
		bool bit_11 = (AlphaFlags & 0x800) != 0;  // 12th bit

		bool bit_12 = (AlphaFlags & 0x1000) != 0; // 13th bit
		bool bit_13 = (AlphaFlags & 0x2000) != 0; // 14th bit
		bool bit_14 = (AlphaFlags & 0x4000) != 0; // 15th bit
		bool bit_15 = (AlphaFlags & 0x8000) != 0; // 16th bit

		bool bit_16 = (AlphaFlags & 0x10000) != 0; // 17th bit
		bool bit_17 = (AlphaFlags & 0x20000) != 0; // 18th bit
		bool bit_18 = (AlphaFlags & 0x40000) != 0; // 19th bit
		bool bit_19 = (AlphaFlags & 0x80000) != 0; // 20th bit

		bool bit_20 = (AlphaFlags & 0x100000) != 0; // 21st bit
		bool bit_21 = (AlphaFlags & 0x200000) != 0; // 22nd bit
		bool bit_22 = (AlphaFlags & 0x400000) != 0; // 23rd bit
		bool bit_23 = (AlphaFlags & 0x800000) != 0; // 24th bit

		bool bit_24 = (AlphaFlags & 0x1000000) != 0; // 25th bit
		bool bit_25 = (AlphaFlags & 0x2000000) != 0; // 26th bit
		bool bit_26 = (AlphaFlags & 0x4000000) != 0; // 27th bit
		bool bit_27 = (AlphaFlags & 0x8000000) != 0; // 28th bit

		bool bit_28 = (AlphaFlags & 0x10000000) != 0; // 29th bit
		bool bit_29 = (AlphaFlags & 0x20000000) != 0; // 30th bit
		bool bit_30 = (AlphaFlags & 0x40000000) != 0; // 31st bit
		bool bit_31 = (AlphaFlags & 0x80000000) != 0; // 32nd bit


		// now its time to convert data
		ConvertToDDS(TextureData, TextureName, Width, Height, SizeOfInitialMip , SizeOfInitialMip, AlphaFlags, mipmap_count, Depth);
		
	}





}

void TXDOpen::ConvertToDDS(std::vector<uint8_t> InputData, std::string TextureName, int Width, int Height, int FirstOffset, int LinearNumber, int AlphaFlags, int MinMapCount
	, int Depth)
{

	

	std::string name = "";

	GlobalFileIndex++;

	TextureName = TextureName.substr(0, TextureName.find('\0')); 
	TextureName.shrink_to_fit();

	name.append(std::string(TextureName));
	name.shrink_to_fit();
	name.append(std::to_string(GlobalFileIndex));
	name.append(".dds");



	std::filesystem::path OutputPath = std::filesystem::path(FilePath) / name;

	std::ofstream Output(OutputPath, std::ios::binary);



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





	int counter = 1;

	int MipOffset = 0;

	int NewWidth = Width / counter;
	int NewHeight = Height / counter;
	int channels = 4;

	int size = FirstOffset; //(NewWidth * NewHeight) * channels;
	//int size = ;

	std::vector<int> MipMapOffsets; 
	MipMapOffsets.push_back(0);


	// ok these work
	for (int i = 0; i < MinMapCount ; i++) {
		
		if (MinMapCount == 1) {
			Output.write(reinterpret_cast<const char*>(InputData.data()), InputData.size());
			continue;
		}

		uint32_t Next = Char_Byte(InputData.begin() + size + MipOffset, InputData.begin() + size + MipOffset + 4).CastToUint32_LE().variable;

		MipOffset += 4;

		MipMapOffsets.push_back(MipOffset + size);

		MipOffset += Next;

	}


	for (int Mip = 0; Mip < MipMapOffsets.size() - 1; ++Mip) {
		

		int Newsize = NewWidth * NewHeight * channels;

		

		int MipStartOffset = MipMapOffsets[Mip];
		int MipEndOffset = MipMapOffsets[Mip + 1];

		MipEndOffset -= 4;


		std::vector<uint8_t> PollFrom = Char_Byte(InputData.begin() + MipStartOffset, InputData.begin()  + MipEndOffset).Char_Bytes;


		int Displacement = MipEndOffset - MipStartOffset;

		uint8_t* ddsPixels = new uint8_t[Displacement];

		//for (int j = 0; j < NewHeight; ++j) {
		//	for (int i = 0; i < NewWidth; ++i) {
		//		int srcIndex = (j * NewWidth + i) * channels;
		//		//int dstIndex = (j * NewWidth + i) * channels;
		//		int dstIndex = srcIndex;

		//		ddsPixels[dstIndex + 0] = PollFrom[srcIndex + 0];
		//		ddsPixels[dstIndex + 1] = PollFrom[srcIndex + 1];
		//		ddsPixels[dstIndex + 2] = PollFrom[srcIndex + 2];
		//		ddsPixels[dstIndex + 3] = PollFrom[srcIndex + 3]; // PollFrom[srcIndex + 3];
		//	}
		//}

		Unswizzle(PollFrom.data(), ddsPixels, NewWidth, NewHeight, channels);

		Output.write(reinterpret_cast<const char*>(ddsPixels), (Displacement));

		delete[] ddsPixels;

		NewWidth = std::max(1, NewWidth / 2);
		NewHeight = std::max(1, NewHeight / 2);

	}
	

	Output.close();

}

void TXDOpen::ConvertToDDSAlt(std::vector<uint8_t> InputData, std::string TextureName, int Width, int Height, int FirstNumber, int LinerNumber, int AlphaFlags, int MimMapCount, int Depth)
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

	WriteInt(Output, LinerNumber, 4);

	WriteInt(Output, 0x00000001, 4);

	WriteInt(Output, MimMapCount, 4);

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





	int counter = 1;

	int MipOffset = 0;

	int NewWidth = Width / counter;
	int NewHeight = Height / counter;
	int channels = 4;

	int size = (NewWidth * NewHeight) * channels;

	std::vector<int> MipMapOffsets;
	MipMapOffsets.push_back(0);


	// ok these work
	for (int i = 0; i < MimMapCount; i++) {

		if (MimMapCount == 1) {
			Output.write(reinterpret_cast<const char*>(InputData.data()), InputData.size());
			continue;
		}

		uint32_t Next = Char_Byte(InputData.begin() + size + MipOffset, InputData.begin() + size + MipOffset + 4).CastToUint32_LE().variable;

		MipOffset += 4;

		MipMapOffsets.push_back(MipOffset + size);

		MipOffset += Next;

	}


	for (int Mip = 0; Mip < MipMapOffsets.size() - 1; Mip++) {


		int Newsize = NewWidth * NewHeight * channels;

		int NewMipMapOffset = MipMapOffsets[Mip];

		std::vector<uint8_t> PollFrom = Char_Byte(InputData.begin() + NewMipMapOffset, InputData.begin() + NewMipMapOffset + Newsize).Char_Bytes;



		uint8_t* ddsPixels = new uint8_t[NewWidth * NewHeight * channels];

		//for (int j = 0; j < NewHeight; ++j) {
		//	for (int i = 0; i < NewWidth; ++i) {
		//		int srcIndex = (j * NewWidth + i) * channels;
		//		//int dstIndex = (j * NewWidth + i) * channels;
		//		int dstIndex = srcIndex;

		//		ddsPixels[dstIndex + 0] = PollFrom[srcIndex + 0];
		//		ddsPixels[dstIndex + 1] = PollFrom[srcIndex + 1];
		//		ddsPixels[dstIndex + 2] = PollFrom[srcIndex + 2];
		//		ddsPixels[dstIndex + 3] = PollFrom[srcIndex + 3]; // PollFrom[srcIndex + 3];
		//	}
		//}

		Unswizzle(PollFrom.data(), ddsPixels, NewWidth, NewHeight, channels);

		Output.write(reinterpret_cast<const char*>(ddsPixels), (NewWidth * NewHeight * channels));

		delete[] ddsPixels;

		NewWidth = std::max(1, NewWidth / 2);
		NewHeight = std::max(1, NewHeight / 2);

	}



	//for (int i = 0; i < InputData.size(); i++) {
	//	WriteInt(Output, InputData[i], 1);
	//}


	//Output.write(reinterpret_cast<const char*>(InputData.data()), InputData.size());
	Output.close();
}


bool TXDOpen::ProcessData(int _ObjectCount)
{
	return false;
}

void TXDOpen::WriteToFile()
{

}
