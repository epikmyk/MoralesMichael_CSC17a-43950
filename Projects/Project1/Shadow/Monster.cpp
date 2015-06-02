#include "Monster.h"
#include "Shadow.h"
#include <stdio.h>
#include <iostream>

Monster::Monster(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int framesX, int framesY, float* passCameraX, float* passCameraY)
	: Shadow(gameRenderer, filePath, x, y, framesX, framesY, passCameraX, passCameraY)
{

}

Monster::~Monster()
{
}

//determines whether monster attacks
void Monster::attack(Monster &monst, Protagonist &player, bool &gameOver)
{
	if (monst.collide(player))
	{
		gameOver = true;
	}
}

// animates monster
void Monster::animate(float speed, float delta, int frameHeight, bool start)
{
	start = true; //set to true before every update
	cropRect.y = frameHeight; //set to frame of row

	//if active do animation
	if (start)
	{
		frameCounter += delta;

		if (frameCounter >= speed)
		{
			frameCounter = 0;
			//get frame of animation
			cropRect.x += frameWidth;
			if (cropRect.x >= textureWidth)
			{
				cropRect.x = 0;
			}
		}
	}
	else
	{
		frameCounter = 0;
		//set frame animation back to start
		cropRect.x = frameWidth;
	}
}
