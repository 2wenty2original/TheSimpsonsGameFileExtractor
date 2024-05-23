
#define SDL_MAIN_HANDLED

#include "Str_Load.h"
#include "RenderToScreen.h"
#include "TextDisplay.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <math.h>


int main(int argc, char** argv){

	RenderToScreen HexEditorLoop = RenderToScreen(1280, 720);

	if (!HexEditorLoop.init()) {
		std::cerr << "Error Could not init" << std::endl;
	}

	while (HexEditorLoop.KeepAlive()) {
		HexEditorLoop.update();
		HexEditorLoop.draw();
	}

	HexEditorLoop.destroy();


	

	return 0;
};