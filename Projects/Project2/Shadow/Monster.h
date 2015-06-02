#pragma once
#include <string>
#include "Shadow.h"
#include "Protagonist.h"

class Monster : public Shadow
{
public:
	Monster(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int framesX, int framesY, float* passCameraX, float* passCameraY);
	~Monster();


	virtual void attack(Monster &monst, Protagonist &player, bool &gameOver);
	void animate(float speed, float delta, int frameHeight, bool start);
	virtual void move(float speed){}

private:


};


