#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class RenderToScreen {

public:

	RenderToScreen(int _width, int _height) {
		width = _width;
		height = _height;


	}

	
	void init();
	void draw();
	void destroy();
	

private:

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* screensurface = nullptr;

	int width;
	int height;

	const int NumMouse = 5;
	bool Keystates[512];
	bool Mousestates[5] = { false };
	bool GameYes = false;

	int x, y;
};