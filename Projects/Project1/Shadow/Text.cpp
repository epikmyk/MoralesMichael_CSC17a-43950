#include "Text.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;


Text::Text(SDL_Renderer* gameRenderer, string input, int size, int x, int y)
{

	finalInput = input.c_str();
	font = TTF_OpenFont("80db.ttf", size);
	color = { 100, 255, 140, 255 };
	textSurface = TTF_RenderText_Solid(font, finalInput, color);
	text = SDL_CreateTextureFromSurface(gameRenderer, textSurface);
	textRect.x = x;
	textRect.y = y;

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_FreeSurface(textSurface);
	textSurface = NULL;
	TTF_CloseFont(font);
	font = NULL;
}


Text::~Text()
{
	SDL_DestroyTexture(text);
	text = NULL;
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = NULL;


}

void Text::drawText(SDL_Renderer* gameRenderer)
{
	SDL_RenderCopy(gameRenderer, text, NULL, &textRect);
}