#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Str_Load.h"
#include "TextDisplay.h"
#include "FontObject.h"
#include "CmdTypeable.h"


class RenderToScreen {

public:

	enum WhichWindow{HexEditor, CommandLine, NA };

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


	


	void CreateWindowf(SDL_Window* &_window, SDL_Renderer* &_renderer, SDL_Surface* &_screensurface, int _width, int _height, const char* title) {


		_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);

		if (_window == NULL) {
			std::cout << "could not init" << std::endl;
			std::cout << SDL_GetError() << std::endl;
			return;
	
		}

		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

		if (_renderer == NULL)
		{
			std::cout << "could not init" << std::endl;
			std::cout << SDL_GetError() << std::endl;
			return;
			
		}

		_screensurface = SDL_GetWindowSurface(_window);

	}

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


		StartIndex -= PotentialXRows;
		EndIndex = SizeOfRenderableLines + PotentialXRows;

		

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


	void Proportions(float TextWidth, float padding) {
		*Segmenet = ((width / 2) / ((width * TextWidth) - padding));
	}


	void CreateSegments(float HowMany, float padding) {
		*Segmenet = ((width / 2) + padding) / HowMany;
	}

	char ScancodeToCharacter(SDL_Scancode Scan) {
		int Offset = 93;
		int Calc = Scan + Offset;
		return (char)Calc;
	}

	

	bool Timer(float& Counter) {

		static float LastTime = 0.0f; 
		float CurrentTime = (float)SDL_GetTicks() / 1000.0f; 

		float ElapsedTime = CurrentTime - LastTime;

	
		/*if (Counter < 0) {
			return true;
		}*/

	
		Counter -= ElapsedTime;

		
		LastTime = CurrentTime;

		
		return Counter < 0;
		
	}


	void GetMouseWindow() {

		int Gx, Gy;

		SDL_GetGlobalMouseState(&Gx, &Gy);
	

		int HexX, HexY, HexW, HexH;
		

		SDL_GetWindowPosition(window, &HexX, &HexY);
		SDL_GetWindowSize(window, &HexW, &HexH);




		int ComX, ComY, ComW, ComH;


		SDL_GetWindowPosition(Cwindow, &ComX, &ComY);
		SDL_GetWindowSize(Cwindow, &ComW, &ComH);

		


		if (Gx > HexX && Gx < HexX + HexW && Gy > HexY && Gy < HexY + HexH) {
			MouseWindowLocation = HexEditor; // overlapping command line
			SDL_SetWindowInputFocus(window);
		}

		else if (Gx > ComX && Gx < ComX + ComW && Gy > ComY && Gy < ComY + ComH) {
			MouseWindowLocation = CommandLine; // overlapping command line
			SDL_SetWindowInputFocus(Cwindow);
		}

		else if (Gx > ComX && Gx < ComX + ComW && Gy > ComY && Gy < ComY + ComH && Gx > HexX && Gx < HexX + HexW && Gy > HexY && Gy < HexY + HexH) {
			MouseWindowLocation = NA; // if they are both overlapping, the windows that is, then NA
		}

		else {
			MouseWindowLocation = NA; //if they are overlapping neither, then NA
		}
	}

	



	

private:

	SDL_Event EventRecorder;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* screensurface = nullptr;

	SDL_Window* Cwindow = nullptr;
	SDL_Renderer* Crenderer = nullptr;
	SDL_Surface* Cscreensurface = nullptr;

	Font* FontObject = nullptr;

	Cmd* CommandLineObject = nullptr;

	std::vector<Text> Lines;
	std::vector<Text> RenderableLines;

	int width;
	int height;


	


	const int NumMouse = 5;
	bool KeyStates[512];
	
	bool Mousestates[5] = { false };
	bool GameYes = false;
	bool CommandType = false;
	bool CanPressKey = true;


	float* xOff = new float();
	float* yOff = new float();

	float* Segmenet = new float();

	int x, y;

	int tolerance = 0;

	int SizeOfLines;
	int SizeOfRenderableLines;

	int MoveIncrement = 0;
	int MoveIncrementStorage = 0;

	int PotentialXRows = 0;
	int PotentialYRows = 0;

	int StartIndex = 0;
	int EndIndex = 0;


	float NumberToResetCounter = 0.2;
	float Counter = 0.2;


	WhichWindow MouseWindowLocation;

	Str_Load* LoadObject;
	
};