#pragma once
#include <SDL.h>
#include <string>	
using namespace std;

class Menu
{
public:
	Menu(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int w, int h);
	~Menu();

	void drawMenu(SDL_Renderer* gameRenderer);

private:
	SDL_Renderer* gameRenderer;
	SDL_Texture* menu;
	SDL_Rect menuRect;
};

