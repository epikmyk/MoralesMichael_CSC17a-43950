#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class Text
{
public:
	Text(SDL_Renderer* gameRenderer, string input, int size, int x, int y);
	~Text();

	void drawText(SDL_Renderer* gameRenderer);

private:
	const char* finalInput;
	SDL_Color color;
	TTF_Font* font;
	SDL_Surface* textSurface;
	SDL_Texture* text;
	SDL_Rect textRect;
	SDL_Renderer* gameRenderer;
};
