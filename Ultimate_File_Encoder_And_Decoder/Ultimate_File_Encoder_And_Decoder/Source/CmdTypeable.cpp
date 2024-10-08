#include "CmdTypeable.h"

void Cmd::init()
{
	
	MouseBar = new SDL_FRect{ 0.f,0.f,2.f,4.f };


}

void Cmd::update(int _x, int _y)
{
	

	

	
}

void Cmd::draw(Font* font)
{
	SDL_Color Colour;

	Colour.r = 200;
	Colour.g = 200;
	Colour.b = 200;
	Colour.a = 255;


	if (SizeOfTyped > 0) {
		for (int i = 0; i < SizeOfTyped; i++) {

			std::string str(1, Typed[i].GetText());

			SDL_Surface* Score = TTF_RenderText_Solid(font->ReturnFont(), str.c_str(), Colour);




			SDL_Texture* ScoreAsATexture = SDL_CreateTextureFromSurface(renderer, Score);

			SDL_FRect TempFRect = Typed[i].GetFRect();

			SDL_RenderCopyF(renderer, ScoreAsATexture, NULL, &TempFRect);



			SDL_DestroyTexture(ScoreAsATexture);
			SDL_FreeSurface(Score);
		}
	}
	

	
}
