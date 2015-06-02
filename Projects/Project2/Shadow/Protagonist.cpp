#include "Protagonist.h"
#include "Shadow.h"
#include <stdio.h>
#include <iostream>

Protagonist::Protagonist(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int framesX, int framesY, float* passCameraX, float* passCameraY)
	: Shadow(gameRenderer, filePath, x, y, framesX, framesY, passCameraX, passCameraY)
{
	airTime = 0;

	isActive = false; //this will determine whethere shadow is moving

	keys[0] = SDL_SCANCODE_LEFT;
	keys[1] = SDL_SCANCODE_RIGHT;
	keys[2] = SDL_SCANCODE_SPACE;
	keys[3] = SDL_SCANCODE_UP;
	keys[4] = SDL_SCANCODE_DOWN;

	jump = false;
}

Protagonist::~Protagonist()
{
}

//push object
void Protagonist::push(Setting &sObject, const Uint8* keyState, float delta)
{
	//if left key is pressed move object to the left
	if (keyState[keys[0]])
	{
		sObject.moveLeft(moveSpeed * delta);
	}
	//if right key is pressed move object to the right
	if (keyState[keys[1]])
	{
		sObject.moveRight(moveSpeed * delta);
	}
}

//interact with object
bool Protagonist::action(const Uint8* keyState)
{
	if (keyState[keys[3]])
	{
		return true;
	}
	return false;
}

//get animation with key input
void Protagonist::update(float delta, const Uint8* keyState, bool fall, bool &right, bool &left)
{
	isActive = true; //set to true before every update
	//if player pressed left arrow
	if (keyState[keys[0]])
	{
		if (getOriginX() > 0 + *cameraX && getOriginX() > 600 + *cameraX && getOriginX() < gameWidth - 600)
		{
			*cameraX = 600 - getOriginX();
			positionRect.x -= moveSpeed * delta;
		}
		else
		{
			if (positionRect.x > 0)
			{
				positionRect.x -= moveSpeed * delta;
			}
		}

		cropRect.y = frameHeight; //set to frame height second row
		left = true;
		right = false;
	}
	//if player presses right arrow
	else if (keyState[keys[1]])
	{
		if (0 + getOriginX() > 600 + *cameraX && getOriginX() < gameWidth - 600)
		{
			positionRect.x += moveSpeed * delta;
			*cameraX = 600 - getOriginX();
		}
		else
		{
			if (positionRect.x < gameWidth - 100)
			{
				positionRect.x += moveSpeed * delta;
			}

		}
		cropRect.y = 0; //set to 0, first row
		right = true;
		left = false;
	}
	else
	{
		isActive = false; //set to false if no keys are pressed
	}
	//if player presses space bar
	if (keyState[keys[2]])
	{

		isActive = false;
		airTime++;
		//if player does not go past this height keep jumping
		if (positionRect.y >= 350 && !fall)
		{
			positionRect.y -= 10;
		}
		jump = true;
	}
	else
	{
		jump = false;
	}

	//bring player back down
	if (airTime > 20 || (!jump && positionRect.y < 500))
	{
		if (positionRect.y < 500)
		{
			isActive = false;
			positionRect.y += 15;
		}
		if (positionRect.y >= 500 && fall)
		{
			positionRect.y += 15;
		}
		if (positionRect.y >= 500)
		{
			airTime = 0;
		}
	}

	//if active do animation
	if (isActive)
	{
		frameCounter += delta;

		if (frameCounter >= 0.15f)
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
		if (positionRect.y < 500)
		{
			cropRect.x = frameWidth;
		}
		else
		{
			if (!jump)
			{
				cropRect.x = 0;
			}
		}
	}
}

void Protagonist::carry(Weapon &weap, const Uint8* keyState, bool right, bool left)
{
	weap.setY(getOriginY());
	//if left key is pressed keep weapon to the left
	if (left)
	{
		weap.setX(getX() - 10);
	}
	//if right key is pressed keep weapon to the right
	if (right)
	{
		weap.setX(getX() + 80);
	}
}

//drop weapon
void Protagonist::drop(Weapon &weap, const Uint8* keyState, bool &carry)
{
	if (keyState[keys[4]])
	{
		weap.setY(600);
		carry = false;
	}

}
