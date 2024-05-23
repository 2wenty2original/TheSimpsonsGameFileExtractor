#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <Eigen/Dense>
#include <iostream>


class Text {
public:

	Text(int _ScreenWidth, int _ScreenHeight, float _PropotionX, float _ProportionY ,int _PositionX, int _PositionY, SDL_Renderer* _renderer) {
		
		renderer = _renderer;
		
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

	void init();
	void update();
	void draw();
	void destroy();

	void SetPos(float _x, float _y) {
		TextFrect->x = _x;
		TextFrect->y = _y;
	}

	void SetSize(float _width, float _height) {
		TextFrect->w = ScreenWidth * _width;
		TextFrect->h = ScreenHeight * _height;


	}

	void SetColour(int r, int g, int b) {
		ColourOfText.x() = r;
		ColourOfText.y() = g;
		ColourOfText.z() = b;
	}

	void SetText(std::string _text) {
		LineOfHex = (char)_text.c_str();
	}

	void SetText(char _text) {
		LineOfHex = _text;
	}

	SDL_FRect* GetFRect() {
		return TextFrect;
	}

	Eigen::Vector3i GetColour() {
		return ColourOfText;
	}

	char GetText() {
		return LineOfHex;
	}

	


private:


	int ScreenWidth;
	int ScreenHeight;

	int TextWidth;
	int TextHeight;

	int TextX;
	int TextY;

	SDL_Renderer* renderer;
	TTF_Font* font;

	
	SDL_FRect* TextFrect;



	Eigen::Vector3i ColourOfText = {255,255,255};

	char LineOfHex;

	
};