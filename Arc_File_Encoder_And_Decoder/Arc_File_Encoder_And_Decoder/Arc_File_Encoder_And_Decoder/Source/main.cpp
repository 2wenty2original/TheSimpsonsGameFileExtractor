#include "Arc_Load.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <math.h>




int main(int argc, char** argv) {

	

	Arc_Load* LoadArcFile = new Arc_Load();
	LoadArcFile->init("stage_twn_d.arc");
	LoadArcFile->CheckHeader();
	LoadArcFile->UnCompress();
	LoadArcFile->ExtractFiles();

	delete LoadArcFile;



	return 0;
};