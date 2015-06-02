#pragma once
#include <string>
#include "Monster.h"

class Dog : public Monster
{
public:
	Dog(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int framesX, int framesY, float* passCameraX, float* passCameraY);
	~Dog();

	void move(float speed);

private:


};


