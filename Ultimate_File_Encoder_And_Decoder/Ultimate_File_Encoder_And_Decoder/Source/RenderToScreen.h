#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Str_Load.h"
#include "TextDisplay.h"


class RenderToScreen {

public:

	RenderToScreen(int _width, int _height) {
		width = _width;
		height = _height;


	}

	
	bool init();
	void update();
	bool KeepAlive();
	void draw();
	void destroy();

	void HandleInput(SDL_Scancode& Keyscancode);
	bool PollEvents();



	bool OutScreen(int x, int y) {
		bool Output;

		if (x < width && x >= 0 && y < height && y >= 0) {
			Output = false;
			return Output;
		}

		else {
			Output = true;
			return Output;
		}
		
	}
	bool Overlap(int x, int y, SDL_FRect Box) {
		if (x > Box.x && x < Box.x + Box.w && y > Box.y && y < Box.y + Box.h) {
			return true;
		}

		else {
			return false;
		}
	}
	

private:

	SDL_Event EventRecorder;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* screensurface = nullptr;

	std::vector<Text> Lines;
	std::vector<SDL_FRect> Frects;

	int width;
	int height;

	const int NumMouse = 5;
	bool KeyStates[512];
	bool Mousestates[5] = { false };
	bool GameYes = false;

	int x, y;



	Str_Load* LoadObject;
	

	//std::string IsItThere = LoadObject->GreaterThan(3);
	//std::string IsItThere2 = LoadObject->LessThan(3);
};