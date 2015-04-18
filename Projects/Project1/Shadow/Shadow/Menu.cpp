#include "Menu.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

Menu::Menu(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int w, int h)
{
	menu = NULL;
	//load image texture for menu object
	menu = IMG_LoadTexture(gameRenderer, filePath.c_str());

	if (menu== NULL)
	{
		cout << "could not load image: " << IMG_GetError();
	}

	menuRect.x = x; //x position of image
	menuRect.y = y; //y position of image
	menuRect.w = w; //width of image
	menuRect.h = h; //height of image
}

Menu::~Menu()
{
	SDL_DestroyTexture(menu);
	menu = NULL;
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = NULL;
}

// draw to screen
void Menu::drawMenu(SDL_Renderer* gameRenderer)
{
	SDL_RenderCopy(gameRenderer, menu, NULL, &menuRect);
}
