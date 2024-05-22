#include "RenderToScreen.h"

void RenderToScreen::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "Could not initialize SDL" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::cout << "could not init" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		std::cout << "could not init" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	screensurface = SDL_GetWindowSurface(window);
}

void RenderToScreen::update()
{


	SDL_GetMouseState(&x, &y);
	//handleinput(EventRecorder.key.keysym.scancode);
}

bool RenderToScreen::KeepAlive()
{
	while (SDL_PollEvent(&EventRecorder)) {
		if (EventRecorder.type == SDL_QUIT) {
			return false;
		}



		if (EventRecorder.type == SDL_KEYDOWN) {
			Keystates[EventRecorder.key.keysym.scancode] = true;


		}

		if (EventRecorder.type == SDL_KEYUP) {
			Keystates[EventRecorder.key.keysym.scancode] = false;
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

void RenderToScreen::draw()
{
	SDL_RenderClear(renderer);
	SDL_GetMouseState(&x, &y);

	SDL_RenderPresent(renderer);
}

void RenderToScreen::destroy()
{

	SDL_DestroyWindow(window);
	SDL_Quit();
}
