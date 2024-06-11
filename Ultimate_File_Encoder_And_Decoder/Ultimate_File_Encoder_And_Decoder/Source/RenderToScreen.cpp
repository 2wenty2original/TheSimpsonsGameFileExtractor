#include "RenderToScreen.h"

bool RenderToScreen::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "Could not initialize SDL" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::cout << "could not init" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		std::cout << "could not init" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	screensurface = SDL_GetWindowSurface(window);

	LoadObject = new Str_Load();
	LoadObject->init("zone02.str");

	
	FontObject = new Font();

	
	
	




	float resetIteration = 0;
	
	

	std::vector<char> List = LoadObject->ReturnAllList();
	


	
	

	float TextWidth = 0.02;
	float TextHeight = 0.02;

	SizeOfLines = List.size();
	
	Lines.resize(SizeOfLines);

	*xOff = 20;
	*yOff = 0;

	*Segmenet = (width / (width * TextWidth));

	

	
//#pragma omp parallel for
	for (int i = 0; i < SizeOfLines; i++) {

		char Temp = List[i];
		int X_Position = (*Segmenet * (i - resetIteration )) + *xOff; //segment is how many on screen, i is the line in question, reset iteration is for responsive webpage thingy
		int Y_Position = *yOff;

		if (OutScreenXBias(X_Position, (width / 2), height)) {

			*yOff += (height * TextHeight);
			resetIteration = i;


		}

		Text NewText = Text(width, height, TextWidth, TextHeight, X_Position, Y_Position, renderer, Temp);

		Lines[i] = NewText;

		NewText.destroy();

		
	}

	std::cout << "complete conversion to text objects" << std::endl;
	
	InitlizeMoveIncrement();


	std::cout << "Each mouse scroll is equal to one line of text height" << std::endl;

	Padding();

	std::cout << " Padding complete " << " " << SizeOfLines << " " << "perfectly rounded i assume" << std::endl;



	InitlizeRenderables();

	std::cout << " renderable Lines Processed " << std::endl;


	CalculateMaxCharacters();

	std::cout << " The Maximum Characters in the viewport has been calculated "<< " " << MaxCharacters << std::endl;

	


	// So far it takes 11 minutes and 12 seconds to open a file that is 1.4k kilobytes big, quite poor performance
	// Release is around 9 minutes and 50 seconds

	// reducing the function call on the std::vector i.e the returnalllist method, reduced it from 10 minutes and 50 seconds to 2 minutes and 32 seconds
	// Release its 2 minutes and 24 seconds



	return true;
}

void RenderToScreen::update()
{
	SDL_GetMouseState(&x, &y);


	
	for (int i = 0; i < SizeOfRenderableLines; i++) {
		if (Overlap(x, y, RenderableLines[i].GetFRect())) {
			std::cout << RenderableLines[i].GetText() << std::endl;
		}
		
		
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

	//SDL_GetMouseState(&x, &y);
	

	for (int i = 0; i < SizeOfRenderableLines; i++) {
		RenderableLines[i].draw(FontObject);
	}



	

	SDL_RenderPresent(renderer);
}

void RenderToScreen::destroy()
{

	delete xOff, yOff;

	SDL_DestroyWindow(window);
	SDL_Quit();
}

void RenderToScreen::HandleInput(SDL_Scancode& Keyscancode)
{

	



	SDL_GetMouseState(&x, &y);


	const Uint8* keystate = SDL_GetKeyboardState(nullptr);

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





		}



		if (EventRecorder.type == SDL_KEYUP) {
			KeyStates[EventRecorder.key.keysym.scancode] = false;



		}

		if (EventRecorder.type == SDL_MOUSEBUTTONDOWN) {
			if (EventRecorder.button.button == SDL_BUTTON_LEFT) {


				


			}

		}

		if (EventRecorder.type == SDL_MOUSEBUTTONUP) {
			if (EventRecorder.button.button == SDL_BUTTON_LEFT) {

				
			}
		}

		if (EventRecorder.type = SDL_MOUSEWHEEL) {
			if (EventRecorder.wheel.preciseY <= -1) {

				//ReCalculateLinesDown();

				for (int i = 0; i < SizeOfRenderableLines; i++) {
					
					RenderableLines[i].SetPos(RenderableLines[i].GetFRect().x, RenderableLines[i].GetFRect().y - MoveIncrement);
					

					//This is scroll down, text goes up tho
				}

				

				
			}

			if (EventRecorder.wheel.preciseY >= 1) {

				

				for (int i = 0; i < SizeOfRenderableLines; i++) {
					
					RenderableLines[i].SetPos(RenderableLines[i].GetFRect().x, RenderableLines[i].GetFRect().y + MoveIncrement);
					
					

					//This is scroll up, text goes down tho
					
				}

				
			}

			

			
			
		}
	}
	return true;
}
