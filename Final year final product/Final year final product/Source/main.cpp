
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
#include <chrono>
#include <numeric>

double StandardDev(const std::vector<double>& times, double &mean)
{
	if (times.size() <= 1) 
	{
		// if nothing then exit
		return 0.0; 
	}

	// calculate the sum of times
	double sum = std::accumulate(times.begin(), times.end(), 0.0);

	//mean calculation
	mean = sum / times.size();

	
	double sq_sum = 0.0;
	for (double time : times)
	{
		sq_sum += (time - mean) * (time - mean);
	}

	// calculate the standard deviation
	double variance = sq_sum / (times.size() - 1);
	return std::sqrt(variance);
}

void run(std::vector<double>& strAdd, std::vector<double>& modelAdd) {

	int counter = 0;

	std::string exitPath;


	auto start = std::chrono::high_resolution_clock::now();

	if (std::filesystem::exists("AllAssets")) {
		for (const auto& entry : std::filesystem::directory_iterator("AllAssets")) {

			if (entry.is_directory()) {
				continue;
			}

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

			std::vector<double> tempModelTimes;

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
						auto startModel = std::chrono::high_resolution_clock::now();

						RwsOpen* RwsObject = new RwsOpen(entryPath);

						RwsObject->FilePath = exitPath;
						RwsObject->GlobalFileIndex = counter++;

						RwsObject->Init();
						RwsObject->ExtractData();

						auto endModel = std::chrono::high_resolution_clock::now();
						std::chrono::duration<double, std::milli> duration = endModel - startModel;
						double msModel = duration.count();
						tempModelTimes.push_back(msModel);

						delete RwsObject;
					}

					else if (extension == ".dff") {
						auto startModel = std::chrono::high_resolution_clock::now();

						DFFOpen* DffObject = new DFFOpen(entryPath);

						DffObject->FilePath = exitPath;
						DffObject->GlobalFileIndex = counter++;

						DffObject->Init();
						DffObject->ExtractData();


						auto endModel = std::chrono::high_resolution_clock::now();
						std::chrono::duration<double, std::milli> duration = endModel - startModel;
						double msModel = duration.count();
						tempModelTimes.push_back(msModel);

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

			double output = 0.0f;
			for (int z = 0; z < tempModelTimes.size(); z++) {
				output += tempModelTimes[z];
			}

			modelAdd.push_back(output);
		
			exitPath.clear();

		}

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> duration = end - start;
		double ms = duration.count();

		strAdd.push_back(ms);
	}
}


void AddToRunTime(int HowMany, std::vector<double>& strAdd, std::vector<double>& modelAdd) {

	for (int i = 0; i < HowMany; i++) {
		run(strAdd, modelAdd);
	}

}


int main(int argc, char** argv) {

	

	std::vector<double> strAdd;
	std::vector<double> modelAdd;

	AddToRunTime(10,strAdd, modelAdd);
	
	double strMean = 0.0f;
	double modelMean = 0.0f;

	double strTime = StandardDev(strAdd, strMean);
	double modelTime = StandardDev(modelAdd, modelMean);
	
	
	
	
	

	

	
	
	return 0;
};