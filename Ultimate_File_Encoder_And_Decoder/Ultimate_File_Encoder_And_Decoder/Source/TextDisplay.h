#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <Eigen/Dense>


class Text {
public:

	Text(int _ScreenWidth, int _ScreenHeight, int _PropotionX, int _ProportionY ,int _PositionX, int _PositionY) {
		ScreenWidth = _ScreenWidth;
		ScreenHeight = _ScreenHeight;

		TextX = _PositionX;
		TextY = _PositionY;


		TextWidth = _ScreenWidth * _PropotionX;
		TextHeight = _ScreenHeight * _ProportionY;

		TextFrect = new SDL_FRect();
		
		TextFrect->w = TextWidth;
		TextFrect->h = TextHeight;
		TextFrect->x = TextX;
		TextFrect->y = TextY;
	}


private:


	int ScreenWidth;
	int ScreenHeight;

	int TextWidth;
	int TextHeight;

	int TextX;
	int TextY;

	
	SDL_FRect* TextFrect;

	Eigen::Vector3i ColourOfText;

	
};