#include "RenderToScreen.h"

bool RenderToScreen::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "Could not initialize SDL" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	CreateWindowf(window, renderer, screensurface, width, height, "Hex Editor"); // hex editor window

	CreateWindowf(Cwindow, Crenderer, Cscreensurface, 500, 300, "Command Line"); // Command line window

	MouseWindowLocation = NA;

	LoadObject = new Str_Load();
	LoadObject->init("zone02.str");

	
	FontObject = new Font();

	CommandLineObject = new Cmd(Crenderer, 500, 300);
	CommandLineObject->init();
	
	





	
	

	std::vector<char> List = LoadObject->ReturnAllList();
	


	
	
	float resetIteration = 0;
	float TextWidth = 0.031;
	float TextHeight = 0.031;


	int row = 0;

	SizeOfLines = List.size();
	
	Lines.resize(SizeOfLines);

	*xOff = 100;
	*yOff = 0;

	//*Segmenet = ((width / 2) / (width * TextWidth));

	//Proportions(TextWidth, 20); // first param is the size of the text as a decimal, Second param is the space between each letter
	CreateSegments(15, -80);
	

	
//#pragma omp parallel for
	for (int i = 0; i < SizeOfLines; i++) {

		char Temp = List[i];
		int X_Position = (*Segmenet * (i - resetIteration )) + *xOff; //segment is how many on screen, i is the line in question, reset iteration is for responsive webpage thingy
		int Y_Position = *yOff;

		row += 1;

		if (OutScreenXBias(X_Position, (width / 2), height)) {


			PotentialXRows = row;
			*yOff += (height * TextHeight);
			resetIteration = i;
			row = 0;

		}

		

		Text NewText = Text(width, height, TextWidth, TextHeight, X_Position, Y_Position, renderer, Temp);

		Lines[i] = NewText;

		NewText.destroy();

		
	}

	std::cout << "complete conversion to text objects" << std::endl;
	

	Padding();

	std::cout << " Padding complete " << " " << SizeOfLines << " " << "perfectly rounded i assume" << std::endl;

	
	
	InitlizeMoveIncrement();


	std::cout << " Move Increment Complete " << std::endl;

	



	InitlizeRenderables();

	std::cout << " renderable Lines Processed " << std::endl;


	

	


	// So far it takes 11 minutes and 12 seconds to open a file that is 1.4k kilobytes big, quite poor performance
	// Release is around 9 minutes and 50 seconds

	// reducing the function call on the std::vector i.e the returnalllist method, reduced it from 10 minutes and 50 seconds to 2 minutes and 32 seconds
	// Release its 2 minutes and 24 seconds


	std::cout << " Init method completed " << std::endl;

	return true;
}

void RenderToScreen::update()
{
	SDL_GetMouseState(&x, &y);

	GetMouseWindow();

	
	/*if (Timer(Counter) == true) {
		std::cout << " Timer Finished " << std::endl;
		Counter = NumberToResetCounter;
	}*/
	
	
	if (MouseWindowLocation == HexEditor) {
		for (int i = StartIndex; i < EndIndex; i++) {

			if (i < 0 || i > SizeOfLines) {

			}

			else {
				if (Overlap(x, y, Lines[i].GetFRect())) {
					std::cout << Lines[i].GetText() << std::endl;
				}
			}

		}
	}

	if (CommandType == true) {
		CommandLineObject->DetermineCharacterIndex(x,y);
	}
	

	
	
	
}

bool RenderToScreen::KeepAlive()
{
	SDL_PumpEvents();

	PollEvents();

	HandleInput(EventRecorder.key.keysym.scancode);



	

	if (SDL_PeepEvents(&EventRecorder, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {

		return false;
	}

	

	return true;
}

void RenderToScreen::draw()
{
	SDL_RenderClear(renderer);
	SDL_RenderClear(Crenderer);

	//SDL_GetMouseState(&x, &y);
	

	

	for (int i = StartIndex; i < EndIndex; i++) {
		if (i < 0 || i > SizeOfLines) {
			
		}

		else {
			Lines[i].draw(FontObject);
		}
		
	}

	if (MouseWindowLocation == CommandLine) {
		CommandLineObject->draw(FontObject);
	}


	
	
	SDL_RenderPresent(renderer);
	SDL_RenderPresent(Crenderer);
}

void RenderToScreen::destroy()
{

	delete xOff, yOff;

	SDL_DestroyWindow(window);
	SDL_DestroyWindow(Cwindow);
	SDL_Quit();
}

void RenderToScreen::HandleInput(SDL_Scancode& Keyscancode)
{

	



	SDL_GetMouseState(&x, &y);


	const Uint8* keystate = SDL_GetKeyboardState(nullptr);


	if (keystate[SDL_SCANCODE_BACKSPACE]) {
		if (CanPressKey == true) {
			CanPressKey = false;
			CommandLineObject->deleting();
		}
		

		if (Timer(Counter) == true) {
			CanPressKey = true;
			Counter = NumberToResetCounter;
		}
	}

	if (keystate[SDL_SCANCODE_W]) {
		for (int i = 0; i < SizeOfRenderableLines; i++) {
			

		}
	}

	if (keystate[SDL_SCANCODE_S]) {
		for (int i = 0; i < SizeOfRenderableLines; i++) {
			

		}
	}

	if (keystate[SDL_SCANCODE_A]) {
		

	}

	if (keystate[SDL_SCANCODE_D]) {
		
	}

	if (keystate[SDL_SCANCODE_E]) {
		
	}

	if (keystate[SDL_SCANCODE_Q]) {
		

	}

	if (keystate[SDL_SCANCODE_Z ]) {


	}




	if (keystate[SDL_SCANCODE_K]) {
		
		


	}


	if (keystate[SDL_SCANCODE_G]) {
		

	}



	
}

bool RenderToScreen::PollEvents()
{

	while (SDL_PollEvent(&EventRecorder)) {
		if (EventRecorder.type == SDL_QUIT) {
			return false;
		}



		if (EventRecorder.type == SDL_KEYDOWN) {
			KeyStates[EventRecorder.key.keysym.scancode] = true;

			if (CommandType == true && EventRecorder.key.keysym.scancode > 3 && EventRecorder.key.keysym.scancode < 30) {
				CommandLineObject->type(ScancodeToCharacter(EventRecorder.key.keysym.scancode));
			}





		}



		if (EventRecorder.type == SDL_KEYUP) {
			KeyStates[EventRecorder.key.keysym.scancode] = false;



		}

		if (EventRecorder.type == SDL_MOUSEBUTTONDOWN) {
			if (EventRecorder.button.button == SDL_BUTTON_LEFT) {
				if (MouseWindowLocation == CommandLine) {
					CommandType = true;
				}

				if (MouseWindowLocation == HexEditor) {
					CommandType = false;
				}

				


			}

		}

		if (EventRecorder.type == SDL_MOUSEBUTTONUP) {
			if (EventRecorder.button.button == SDL_BUTTON_LEFT) {

				
			}
		}

		if (EventRecorder.type = SDL_MOUSEWHEEL) {
			if (EventRecorder.wheel.preciseY <= -1) {


				
				if (MouseWindowLocation == HexEditor) {
					for (int i = StartIndex; i < EndIndex; i++) {

						if (i < 0 || i > SizeOfLines) {

						}

						else {
							Lines[i].SetPos(Lines[i].GetFRect().x, Lines[i].GetFRect().y - 30);
						}




						//This is scroll down, text goes up tho
					}

					StartIndex += PotentialXRows;
					EndIndex += PotentialXRows;
				}
				

				
			}

			if (EventRecorder.wheel.preciseY >= 1) {


				if(MouseWindowLocation == HexEditor){
					for (int i = StartIndex; i < EndIndex; i++) {


						if (i < 0 || i > SizeOfLines) {

						}

						else {
							Lines[i].SetPos(Lines[i].GetFRect().x, Lines[i].GetFRect().y + 30);
						}



						//This is scroll up, text goes down tho

					}


					StartIndex -= PotentialXRows;
					EndIndex -= PotentialXRows;

				}
				
			}

			

			
			
		}
	}
	return true;
}
