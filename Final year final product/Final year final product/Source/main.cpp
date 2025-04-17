
#include "Str_Load.h"
#include "Str_Load_Full.h"
#include "Str_Confirmer.h"
#include "TXDOpen.h"
#include "RWSOpen.h"
#include "DFFOpen.h"
#include "BSPOpen.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <math.h>
#include <memory>




int main(int argc, char** argv) {

	int counter = 0;



	std::string exitPath;

	if (std::filesystem::exists("AllAssets")) {
		for (const auto& entry : std::filesystem::directory_iterator("AllAssets")) {

			std::string entryPath = entry.path().string();

			std::string prefix = "AllAssets";



			// this will extract the file name, - 3 for the extentsion and AllAssets because of the folder, this does work now
			exitPath.insert(exitPath.begin(), entryPath.begin() + prefix.length() + 1, entryPath.end() - 4);

			if (!std::filesystem::exists(exitPath.c_str())) {
				std::filesystem::create_directory(exitPath.c_str());


			}


			Str_Confirmer* ConfirmStreamFile = new Str_Confirmer();
			ConfirmStreamFile->Init(entryPath.c_str());
			int Global = ConfirmStreamFile->ReadHeader();

			if (Global == 0) {
				Str_Load* StrObject = new Str_Load();

				StrObject->USFP = exitPath + "/" + "Uncompressed_Sections";
				StrObject->ExtractedSection = exitPath + "/" + "Files";

				StrObject->init(entryPath.c_str()); // land of chocolate zone02
				StrObject->CheckHeaderForCompression();
				StrObject->UnCompress();
				StrObject->ExtractFiles();


				delete StrObject;
			}

			else if (Global == 1) {
				Str_Load_Full* StrObject = new Str_Load_Full();

				StrObject->USFP = exitPath + "/" + "Uncompressed_Sections";
				StrObject->ExtractedSection = exitPath + "/" + "Files";

				StrObject->init(entryPath.c_str()); // land of chocolate zone02
				StrObject->CheckHeaderForCompression();
				StrObject->UnCompress();
				StrObject->ExtractFiles();


				delete StrObject;
			}
			
			delete ConfirmStreamFile;
		


			if (std::filesystem::exists(exitPath)) {
				std::cout << exitPath << " " << "/" << "Files" << std::endl;
				for (const auto& entry : std::filesystem::directory_iterator(exitPath + "/" + "Files")) {
					

					std::string entryPath = entry.path().string();

					std::string extension;

					extension.insert(extension.begin(), entryPath.end() - 4, entryPath.end());

					
					// these are files that contain geometry
					if (extension != ".rws" && extension != ".dff" && extension != ".txd" && extension != ".bsp") {
						continue;
					}

				

					if (extension == ".rws") {
						RwsOpen* RwsObject = new RwsOpen(entryPath);

						RwsObject->FilePath = exitPath;
						RwsObject->GlobalFileIndex = counter++;

						RwsObject->Init();
						RwsObject->ExtractData();

						delete RwsObject;
					}

					else if (extension == ".dff") {
						DFFOpen* DffObject = new DFFOpen(entryPath);

						DffObject->FilePath = exitPath;
						DffObject->GlobalFileIndex = counter++;

						DffObject->Init();
						DffObject->ExtractData();

						delete DffObject;

					}

					/*else if (extension == ".txd") {
						TXDOpen* TXDObject = new TXDOpen(entryPath);

						TXDObject->FilePath = exitPath;
						TXDObject->GlobalFileIndex = counter++;

						TXDObject->Init();
						TXDObject->ExtractData();

						delete TXDOpen;
					}*/

				/*	else if (extension == ".bsp") {
						BSPOpen* BSPObject = new BSPOpen(entryPath);

						BSPObject->FilePath = exitPath;
						BSPObject->GlobalFileIndex = counter++;

						BSPObject->Init();
						BSPObject->ReadHeader();
						BSPObject->WriteToFile();

						delete BSPObject;
					}*/

					
					

				}
			}

			exitPath.clear();

		}
	}

	

	
	
	
	
	
	

	

	
	
	return 0;
};