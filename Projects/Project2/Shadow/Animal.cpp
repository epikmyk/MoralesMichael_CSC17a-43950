#include "Animal.h"
#include "Shadow.h"
#include <SDL_image.h>
#include <iostream>

Animal::Animal(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int framesX, int framesY, float* passCameraX, float* passCameraY)
	: Shadow(gameRenderer, filePath, x, y,
	framesX, framesY, passCameraX, passCameraY)
{
	
}

Animal::~Animal()
{
}

void Animal::flyLeft(int x)
{
	x += 5;
	setX(x);
}
