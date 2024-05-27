#include "TextDisplay.h"

void Text::init()
{
	int init = TTF_Init();

	if (init != 0) {
		std::cout << SDL_GetError() << std::endl;
	}

	font = TTF_OpenFont("assets/in/Font.ttf", 12);

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

	Colour.r = ColourOfText.x();
	Colour.g = ColourOfText.y();
	Colour.b = ColourOfText.z();

	


	SDL_Surface* Score = TTF_RenderText_Solid(font, LineOfHex.c_str(), Colour);
	



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

void Text::OverlapEachLetterHightlight(int &x, int &y)
{
	Eigen::Vector2f Maximum = {(TextFrect->x + TextFrect->w), (TextFrect->y + TextFrect->h)};
	float Segment = (TextFrect->w - TextFrect->x) / LineOfHex.size();
	for (int i = 0; i < LineOfHex.size(); i++) {
		float AddToFrect = i * Segment;
		SDL_FRect CharacterFrect = { TextFrect->x + AddToFrect,TextFrect->y,TextFrect->x + Segment, TextFrect->h};
		if (x > CharacterFrect.x && x < CharacterFrect.x + CharacterFrect.w && y > CharacterFrect.y && y < CharacterFrect.y + CharacterFrect.h) {
			std::cout << LineOfHex[i] << std::endl;
		}
	
	}
}
