#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>


class Font {

public:

	Font() {

		int init = TTF_Init();

		if (init != 0) {
			std::cout << SDL_GetError() << std::endl;
		}

		font = TTF_OpenFont("assets/in/Arial.ttf", 12);

		if (font == NULL) {
			std::cout << SDL_GetError() << std::endl;
		}
	}

	~Font() {
		TTF_CloseFont(font);
	}

	void destroy() {
		TTF_CloseFont(font);
	}

	TTF_Font* ReturnFont() {
		return font;
	}


private:


	TTF_Font* font;

};