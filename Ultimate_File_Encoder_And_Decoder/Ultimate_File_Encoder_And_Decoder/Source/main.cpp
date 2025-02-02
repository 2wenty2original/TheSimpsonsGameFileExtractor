
#define SDL_MAIN_HANDLED

#include "Str_Load.h"
#include "RenderToScreen.h"
#include "TextDisplay.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <math.h>
#include "DisplayByte.h"



int main(int argc, char** argv){

	/*RenderToScreen HexEditorLoop = RenderToScreen(1280, 720);

	if (!HexEditorLoop.init()) {
		std::cerr << "Error Could not init" << std::endl;
	}

	while (HexEditorLoop.KeepAlive()) {
		HexEditorLoop.update();
		HexEditorLoop.draw();
	}

	HexEditorLoop.destroy();*/



	//std::vector<int> Test = {0x53,0x54,0x6F,0x63};





	Str_Load* StrObject = new Str_Load();
	StrObject->init("zone02.str"); // land of chocolate zone02
	StrObject->CheckHeaderForCompression();
	StrObject->UnCompress();
	StrObject->ExtractFiles();
	
	
	
	
	

	

	
	
	

	return 0;
};