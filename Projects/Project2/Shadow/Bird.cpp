#include "Bird.h"
#include <stdio.h>
#include <iostream>


Bird::Bird(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int framesX, int framesY, float* passCameraX, float* passCameraY)
	: Monster(gameRenderer, filePath, x, y, framesX, framesY, passCameraX, passCameraY)
{
	scaredBirds = false;
}

Bird::~Bird()
{
}

void Bird::move(float speed)
{

    //fly up
	if (positionRect.x < 12500 || scaredBirds)
	{
		if (!scaredBirds)
		{
			positionRect.y -= speed;
		}
		if (scaredBirds && positionRect.y > -100)
		{
			positionRect.y -= speed;
		}
	}
	if (!scaredBirds)
	{
		//fly to the left
		positionRect.x -= speed;
	}

	//get frame position for animation
	if (cropRect.x == frameWidth * 7)
	{
		cropRect.x = frameWidth;
	}
}

void Bird::attack(Protagonist &player, Projectile &pebble, bool &gameOver, bool &hitBird)
{
	//determine if player collides with bird
	if (collide(player))
	{
		gameOver = true;
	}
	//determine if pebble collides with bird
	if (collide(pebble) && !collide(player))
	{
		hitBird = true;
	}
	
}

void Bird::scared(bool scaredB)
{
	scaredBirds = scaredB;
}