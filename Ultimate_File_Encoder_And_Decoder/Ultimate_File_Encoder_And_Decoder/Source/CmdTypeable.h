#pragma once
#include <iostream>
#include <vector>
#include "TextDisplay.h"
#include "FontObject.h"
#include "Str_Load.h"
#include "FontObject.h"
#include "TextDisplay.h"
#include <SDL_image.h>
#include <SDL.h>

class Cmd {

	struct Vector2D {
		int x;
		int y;
	};

	public:

		Cmd(SDL_Renderer* _renderer, int _width, int _height) 
		{
			width = _width;
			height = _height;
			renderer = _renderer;

			LineFrect = new SDL_FRect();

			LineFrect->x = 0;
			LineFrect->y = height / 2;
			LineFrect->w = width - 10;
			LineFrect->h = 30;

			
		};

		void init();
		void update(int _x, int _y);
		void draw(Font* font);
		void destroy();

		void InsertBetween(std::vector<Text> &v, int index, Text text) {
			auto insertion = v.begin() + index;




			auto Start = v.begin() + index + 1;
			auto End = v.end();

			std::vector<Text> TempVec(Start, End);

			v.insert(insertion, text);

			v.erase(Start, End);

			
		}


		void type(char character) {

			
			if (typeIndex < PreDefinedSize) {


				/*Text TempText = Text(width, height, 0, 0, (typeIndex * (width / PreDefinedSize)) + Offset, height / 2, renderer, character);

				TempText.SetSize((width / PreDefinedSize) + Offset, 20 + Offset);

				Typed.push_back(TempText);

				SizeOfTyped = Typed.size();

				typeIndex += 1;

				TempText.destroy();*/


				Text TempText = Text(width, height, 0, 0, (typeIndex * (width / PreDefinedSize)) + Offset, height / 2, renderer, character);

				TempText.SetSize((width / PreDefinedSize) + Offset, 20 + Offset);

				if (typeIndex > SizeOfTyped - 1) {
					Typed.push_back(TempText);

					SizeOfTyped = Typed.size();

					typeIndex += 1;

					TempText.destroy();
				}

				else if (typeIndex < 0) {
					typeIndex = 0;
				}

				else {

					Typed.insert(Typed.begin() + typeIndex, TempText);
					//Typed.

				}

				
			}
			

			
		}

		void deleting() {
			if (typeIndex > 0 && typeIndex <= PreDefinedSize) {
				Typed.erase(Typed.begin() + typeIndex - 1);
				SizeOfTyped = Typed.size();
				typeIndex -= 1;
			}
		}

		void DetermineCharacterIndex(int _x, int _y) {
			for (int i = 0; i < SizeOfTyped; i++) {
				SDL_FRect TempFrect = Typed[i].GetFRect();

				if (_x > TempFrect.x && _x < TempFrect.x + TempFrect.w && _y > TempFrect.y && _y < TempFrect.y + TempFrect.h) {
					MouseIndexLocation = i;
				}
			}
		}


		void ReturnTextAtIndex(int i) {

		}

		void IncrementTypeIndex() {
			if (typeIndex < SizeOfTyped) {
				typeIndex += 1;
			}
		}

		void DecrementTypeIndex() {
			if (typeIndex > 1) {
				typeIndex -= 1;
			}
		}

		


		void SetType(bool YayOrNay) {
			CanType = YayOrNay;
		}

		bool GetType() {
			return CanType;
		}




	private:

		//std::string Typed; // all the characters that have been typed

		std::vector<Text> Typed;

		SDL_Renderer* renderer = nullptr;

		bool CanType; // am i able to type

		int PreDefinedSize = 100; // maximum command limit, also pre-allocates vector, far quicker.

		int width;
		int height;

		int Offset = 40;

		int SizeOfTyped = 0;

		int typeIndex = 0; // used for when typing and checking
		int MouseIndexLocation = 0; // i.e when i click on text which character is the line next too

		SDL_FRect* LineFrect = nullptr;

		SDL_FRect* MouseBar = nullptr;
		

};