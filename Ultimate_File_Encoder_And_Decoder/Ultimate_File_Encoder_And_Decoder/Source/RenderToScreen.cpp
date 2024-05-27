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

	sizeof(LoadObject);

	

	float xOff = 10;
	float yOff = 10;

	

	float resetCounter = 0;

	
	int size = LoadObject->ReturnAllList().size();
	std::vector<std::string> StringList = LoadObject->ReturnAllList();
	
	//#pragma omp parallel for
	for (int i = 0; i < size; i++) {
		std::string Temp = StringList[i];

		int xPos = (i + 1) * xOff;
		xPos -= resetCounter;

		int yPos = 1 + yOff;

		if (this->OutScreen(xPos, yPos) == true) {

			yOff += 5;
			resetCounter += xPos;


		}

		Text* NewText = new Text(width, height, 0.2, 0.2, xPos, yPos, renderer);

		NewText->init();
		NewText->SetText(Temp);
		NewText->SetColour(252,252,252);

		Lines.push_back(NewText);
		
		NewText->destroy();

		delete[] NewText;



	}
	

	std::cout << "complete" << std::endl;








	return true;
}

void RenderToScreen::update()
{
	SDL_GetMouseState(&x, &y);



	for (int i = 0; i < Lines.size(); i++) {
		if (this->OutScreen(Lines[i]->GetFRect()->x, Lines[i]->GetFRect()->y) == false) {
			Lines[i]->OverlapEachLetterHightlight(x, y);
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

	for (int i = 0; i < Lines.size(); i++) {
		if (this->OutScreen(Lines[i]->GetFRect()->x, Lines[i]->GetFRect()->y) == false) {
			
			Lines[i]->draw();
		}
	}

	

	SDL_RenderPresent(renderer);
}

void RenderToScreen::destroy()
{

	SDL_DestroyWindow(window);
	SDL_Quit();
}

void RenderToScreen::HandleInput(SDL_Scancode& Keyscancode)
{

	



	SDL_GetMouseState(&x, &y);

	











	const Uint8* keystate = SDL_GetKeyboardState(nullptr);

	if (keystate[SDL_SCANCODE_W]) {
		
	}

	if (keystate[SDL_SCANCODE_S]) {
		
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
	}
	return true;
}
