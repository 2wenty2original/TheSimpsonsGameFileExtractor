#include "FileOpen.h"



int main(int argc, char** argv) {

	FileOpen fileinsert = FileOpen("Load1.rws");
	fileinsert.Init();
	fileinsert.DeterminePoints();



	return 0;
}