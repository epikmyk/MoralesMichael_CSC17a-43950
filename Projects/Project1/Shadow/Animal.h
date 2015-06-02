#pragma once
#include <SDL.h>
#include <string>	
#include "Shadow.h"


using namespace std;

class Animal : public Shadow
{
public:
	Animal(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int framesX, int framesY, float* passCameraX, float* passCameraY);
		
	~Animal();

	void flyLeft(int x);
};

