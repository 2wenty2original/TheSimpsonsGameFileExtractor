#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Str_Load.h"
#include "TextDisplay.h"
#include "FontObject.h"


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

	bool IsValidIndex(int index, int Offset, int SizeOfContainer) {
		if ((index + Offset) >= 0 && (index + Offset) < SizeOfContainer) {
			return true;
		}

		else {
			return false;
		}
	}

	bool LessOrMoreIndex(int index, int Offset, int SizeOfContainer) {
		if ((index + Offset) >= 0) {
			return false;
		}

		else if ((index + Offset) < SizeOfContainer) {
			return true;
		}
	}


	void AdjustLines() {

		float Calc = Lines[0].GetFRect().w;
		Calc = width / Calc;
		Calc = int(Calc);

		
	}

	void InitlizeRenderables() {

		RenderableLines.clear();

		for (int i = 0; i < SizeOfLines; i++) {
			if (OutScreen(Lines[i].GetFRect().x, Lines[i].GetFRect().y, (width / 2), height) == false) {
				RenderableLines.push_back(Lines[i]);
			}
		}

		SizeOfRenderableLines = RenderableLines.size();

		

	}

	void ReCalculateLinesUp() {


		//RenderableLines.insert(RenderableLines.end(), Lines.begin() + CurrentIndex + LastIndex, Lines.begin() + CurrentIndex + LastIndex + 100);

		MovingIndex -= MaxWidth;

		RenderableLines.clear();
		
		if (MovingIndex > SizeOfLines) {
			MovingIndex = SizeOfLines - 1;
		}

		if (MovingIndex - (MaxCharacters / 2) > 0) {
			RenderableLines.insert(RenderableLines.begin(), Lines.begin() + MovingIndex - (MaxCharacters / 2), Lines.begin() + MovingIndex);
		}
		

 		SizeOfRenderableLines = RenderableLines.size();

		//std::cout << "finished" << std::endl;

		
	}


	void ReCalculateLinesDown() {
		

		//RenderableLines.insert(RenderableLines.begin(), Lines.begin() + CurrentIndex + LastIndex, Lines.begin() + CurrentIndex + LastIndex + 100);
		
		MovingIndex += 1;
		
		for (int i = 0; i < MaxWidth; i++) {
			int InverseIndex = MaxWidth - i;
			RenderableLines.push_back(Lines[SizeOfRenderableLines + i + MovingIndex]);
			RenderableLines.erase(RenderableLines.begin() + InverseIndex);
		}

		

		SizeOfRenderableLines = RenderableLines.size();
	}

	bool OutScreen(int x, int y, int _width, int _height) {
		bool Output;

		if (x < _width && x >= 0 && y < _height && y >= 0) {
			Output = false;
			return Output;
		}

		else {
			Output = true;
			return Output;
		}
		
	}


	bool OutScreenXBias(int x, int _width, int _height) {
		bool Output;

		if (x < _width && x >= 0) {
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


	bool Overlap(SDL_FRect Overlap, SDL_FRect Overlapped) {
		if (Overlap.x > Overlapped.x && Overlap.x < Overlapped.x + Overlapped.w && y > Overlapped.y && Overlap.y < Overlapped.y + Overlapped.h) {
			return true;
		}

		else {
			return false;
		}
	}

	void InitlizeMoveIncrement() {
		MoveIncrement = Lines[0].GetFRect().h + 25;
	}

	void Padding() {

		int Calc = width / Lines[0].GetFRect().w;
		int Counter = 0;

		float Sum = SizeOfLines % Calc;

		int AmountOfPad = Calc - Sum;



		for (int i = 0; i < AmountOfPad; i ++) {
			Text TempText = Text(width,height,0.01f,0.01f, 999999999,999999999,renderer, (const char)".");
			Lines.push_back(TempText);

			
		}

		SizeOfLines = Lines.size();
	}

	void CalculateMaxCharacters() {
		MaxWidth = (width / 2) / Lines[0].GetFRect().w;
		MaxHeight = height / Lines[0].GetFRect().h;
		MaxCharacters = MaxWidth * MaxHeight;

	}


	

private:

	SDL_Event EventRecorder;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* screensurface = nullptr;

	Font* FontObject = nullptr;

	std::vector<Text> Lines;
	std::vector<Text> RenderableLines;

	//std::vector<SDL_FRect> Frects;

	int width;
	int height;

	const int NumMouse = 5;
	bool KeyStates[512];
	
	bool Mousestates[5] = { false };
	bool GameYes = false;


	float* xOff = new float();
	float* yOff = new float();

	float* Segmenet = new float();



	int x, y;


	int LastIndex = 0;
	int CurrentIndex = 0;

	int SizeOfLines;
	int SizeOfRenderableLines;

	int MoveIncrement = 0;
	int MoveIncrementStorage = 0;


	int MaxWidth = 0;
	int MaxHeight = 0;
	int MovingIndex = 0; 
	int MaxCharacters = 0;



	Str_Load* LoadObject;
	

	//std::string IsItThere = LoadObject->GreaterThan(3);
	//std::string IsItThere2 = LoadObject->LessThan(3);
};