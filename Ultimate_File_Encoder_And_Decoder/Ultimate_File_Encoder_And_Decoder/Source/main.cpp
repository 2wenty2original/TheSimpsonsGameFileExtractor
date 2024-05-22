
#define SDL_MAIN_HANDLED

#include "Str_Load.h"
#include "RenderToScreen.h"
#include "TextDisplay.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <math.h>


int main(int argc, char** argv){

	Str_Load* LoadObject = new Str_Load("e.str");
	LoadObject->init();
	//std::string IsItThere = LoadObject->GreaterThan(3);
	//std::string IsItThere2 = LoadObject->LessThan(3);

	return 0;
};