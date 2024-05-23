#include "TextDisplay.h"

void Text::init()
{
	int init = TTF_Init();
	if (init != 0) {
		std::cout << SDL_GetError() << std::endl;
	}

	font = TTF_OpenFont("assets/Font.ttf", 12);

	if (font == NULL) {
		std::cout << SDL_GetError() << std::endl;
	}
}

void Text::update()
{


}

void Text::draw()
{
	SDL_Color Colour;

	Colour.r = static_cast<Uint8>(ColourOfText.x());
	Colour.g = static_cast<Uint8>(ColourOfText.y());
	Colour.b = static_cast<Uint8>(ColourOfText.z());

	


	SDL_Surface* Score = TTF_RenderText_Solid(font, &LineOfHex, Colour);



	SDL_Texture* ScoreAsATexture = SDL_CreateTextureFromSurface(renderer, Score);



	SDL_RenderCopyF(renderer, ScoreAsATexture, NULL, TextFrect);



	SDL_DestroyTexture(ScoreAsATexture);
	SDL_FreeSurface(Score);
}

void Text::destroy()
{
	delete TextFrect;
	TTF_CloseFont(font);

}
