#include "Arc_load.h"



void Arc_Load::init(const char* file)
{
	Filename = (char*)file;

	std::ifstream EntireFile(Filename, std::ios::binary | std::ios::ate);
	if (!EntireFile.is_open()) {
		std::cerr << "Cannot open file: " << Filename << "\n";
		return;
	}


	std::streamsize fileSize = EntireFile.tellg();
	EntireFile.seekg(0, std::ios::beg);

	if (fileSize <= 0) {
		std::cerr << "File size invalid or empty file: " << Filename << "\n";
		return;
	}

	std::vector<char> buffer(fileSize);

	if (!EntireFile.read(buffer.data(), fileSize)) {
		std::cerr << "Failed to read file content.\n";
		return;
	}

	EntireFile.close();

	for (char ch : buffer) {
		SortGarbeld(std::string(1, ch));  
	}

    std::cout << "Completed the Init " << buffer.size() << " Is the Buffer Size\n";

}



void Arc_Load::WriteSectionToFile(std::ofstream& OutFile, std::vector<uint8_t> Data, int index)
{
	if (!OutFile.is_open()) {
		return;
	}

	std::string Name = std::to_string(index);

	if (!Data.empty()) {
		OutFile.write((const char*)(Data.data()), Data.size());
	}
}

void Arc_Load::WriteSectionToFile(std::ofstream& OutFile, std::vector<uint8_t> Data)
{
	if (!OutFile.is_open()) {
		return;
	}

	if (!Data.empty()) {
		OutFile.write((const char*)(Data.data()), Data.size());
	}
}

void Arc_Load::UnCompressSection(std::vector<char> InData,std::vector<uint8_t> &OutData, size_t InSize, size_t OutSize)
{
	
	
}

void Arc_Load::UnCompress()
{
	
}


void Arc_Load::SortGarbeld(std::string CurrentLine) {

	int Size = CurrentLine.size();

	for (int j = 0; j < Size; j++) {

		AllList.push_back(CurrentLine[j]);

	
	
	}	
}

void Arc_Load::SortGarbeld(std::string CurrentLine, std::vector<uint8_t>& Output) {
	int Size = CurrentLine.size();

	for (int j = 0; j < Size; j++) {

		Output.push_back(CurrentLine[j]);



	}
}

		
void Arc_Load::CheckHeader()
{

	// Basically how the .Arc file is constructed is as such
	// there are "sections" that contain information related to navigating the file, these include the GLOBAL offsets in the file
	// the length of the file, flags denoting information and the file itself


	int Offset = 0;


	// this is a revised version of the Marathon code, this code is in c++ and uses more fluid stack allocation
	// for reference, c# code uses a global read object, whilst mine merely grabs chunks of already existing byte blocks
	
	// this should be like 140 thousand or some bullshit, doesnt matter i have other authenticators but good to debug
	int Signature = Char_Byte(AllList.begin(), Offset, 4).CastToint32_BE().variable;

	int entrysize = 16;


	// this is the start of the entrys
	int Start = Char_Byte(AllList.begin(), Offset, 4).CastToint32_BE().variable;

	
	// this is the start of the dictionary

	int DictionaryStart = Char_Byte(AllList.begin(), Offset, 4).CastToint32_BE().variable;


	// this is the start of the ACTUAL data of the first file

	int DataStart = Char_Byte(AllList.begin(), Offset, 4).CastToint32_BE().variable;

	Offset += Start;

	Section ArchiveFileSection = Section(&AllList, Offset);

	uint32_t StringTable = Start + (ArchiveFileSection.Length * entrysize);

	std::vector<Section> Entries(ArchiveFileSection.Length);

	Entries[0] = ArchiveFileSection;

	// we start at one because we have already done zero, zero is our root, because this is a hierachy, because i hate my life

	

	for (int i = 1; i < ArchiveFileSection.Length; i++) {
		Entries[i] = Section(&AllList, Offset);
	}




	AllList.clear();
	AllList.shrink_to_fit();
}



bool Arc_Load::IsArcFile(std::ifstream& file)
{

	std::string Line;
	uint16_t Arc = 0x55AA;

	std::getline(file, Line);

	if (Line == std::to_string(Arc)) {
		file.close();
		return true;
	}

	else {
		file.close();
		return false;
	}

	return false;
}

void Arc_Load::ExtractSection(const char* FileName)
{
	
	




	

}

void Arc_Load::ExtractFiles()
{
	// this is done to load in the section folder, we are not making a new one dw
	std::filesystem::path folder(USFP);

	if (!std::filesystem::exists(folder) || !std::filesystem::is_directory(folder)) {
		return;
	}

	ExtractedSection = "Files";

	// this will create a new folder to which all extracted files are put into

	if (!std::filesystem::exists(ExtractedSection.c_str())) {
		if (std::filesystem::create_directory(ExtractedSection.c_str())) {
			std::cout << " Created the folder " << " " << ExtractedSection.c_str() << std::endl;
		}

	}

	// gets every file from folder, determins if they are an acceptable file

	for(const auto &entry : std::filesystem::directory_iterator(folder)) {
		if (std::filesystem::is_regular_file(entry)) {  
			std::string TempString = entry.path().string();
			FileNames.push_back(TempString);
		}
	}

	

	for (int i = 0; i < FileNames.size(); i++) {
		ExtractSection(FileNames[i].c_str());
	}
}

void Arc_Load::ConvertToTxt()
{

}

void Arc_Load::ConvertToStr()
{

}

void Arc_Load::destroy()
{

}


