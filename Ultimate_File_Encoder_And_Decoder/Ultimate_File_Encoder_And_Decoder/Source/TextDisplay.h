#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <Eigen/Dense>
#include <iostream>
#include "FontObject.h"

class Text {
public:

	Text() {};
	

	Text(float _ScreenWidth, float _ScreenHeight, float _PropotionX, float _ProportionY, float _PositionX, float _PositionY, SDL_Renderer* _renderer, char Text)
		: renderer(_renderer) {

	
		TextFrect = SDL_FRect();

		TextFrect.w = _ScreenWidth * _PropotionX;
		TextFrect.h = _ScreenHeight * _ProportionY;
		TextFrect.x = _PositionX;
		TextFrect.y = _PositionY;

		//this->init();
		this->SetText(Text);
		this->SetColour(200,200, 200);
	}

	void init();
	void update();
	void draw(Font* font);
	void destroy();

	void OverlapEachLetterHightlight(int& x, int& y);

	void SetPos(float _x, float _y) {
		TextFrect.x = _x;
		TextFrect.y = _y;
	}

	void SetSize(float ScreenWidth, float ScreenHeight, float _width, float _height) {
		TextFrect.w = ScreenWidth * _width;
		TextFrect.h = ScreenHeight * _height;
	}

	void SetColour(int r, int g, int b) {
		ColourOfText.x() = r;
		ColourOfText.y() = g;
		ColourOfText.z() = b;
	}

	void SetText(char _text) {
		LineOfHex = _text;
	}

	SDL_FRect GetFRect() {
		return TextFrect;
	}

	Eigen::Vector3i GetColour() {
		return ColourOfText;
	}

	void SetColour(Eigen::Vector3i colour) {
		ColourOfText = colour;
	}


	void SetColour(float r, float g, float b) {
		ColourOfText.x() = r;
		ColourOfText.y() = g;
		ColourOfText.z() = b;

	}

	char GetText() {
		return LineOfHex;
	}




private:

	SDL_Renderer* renderer;


	SDL_FRect TextFrect;

	Eigen::Vector3i ColourOfText = { 255,255,255 };

	char LineOfHex;


};