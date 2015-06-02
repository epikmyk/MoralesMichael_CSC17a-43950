#include "Dog.h"
#include <stdio.h>
#include <iostream>


Dog::Dog(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int framesX, int framesY, float* passCameraX, float* passCameraY)
	: Monster(gameRenderer, filePath, x, y, framesX, framesY, passCameraX, passCameraY)
{

}

Dog::~Dog()
{
}

void Dog::move(float speed)
{
	positionRect.x -= speed;
}
