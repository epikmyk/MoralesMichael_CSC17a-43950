#include "Shadow.h"
#include <SDL_image.h>
#include <iostream>

Shadow::Shadow(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int framesX, int framesY, float* passCameraX, float* passCameraY)
{

	shadow = NULL;
	shadow = IMG_LoadTexture(gameRenderer, filePath.c_str());

	if (shadow == NULL)
	{
		cout << "could not load image: " << IMG_GetError();
	}

	SDL_QueryTexture(shadow, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = x; //x position on screen
	positionRect.y = y; //y position on screen

	textureWidth = cropRect.w; //width of image

	cropRect.w /= framesX; //width of cropped image
	cropRect.h /= framesY; //height of cropped image

	frameWidth = positionRect.w = cropRect.w; //frame width 
	frameHeight = positionRect.h = cropRect.h; //frame height 

	originX = frameWidth / 2 ;
	originY = frameHeight / 2;
	radius = frameWidth * static_cast<float>(3)/4;
	airTime = 0;

	isActive = false; //this will determine whethere shadow is moving

	keys[0] = SDL_SCANCODE_LEFT;
	keys[1] = SDL_SCANCODE_RIGHT;
	keys[2] = SDL_SCANCODE_SPACE;
	keys[3] = SDL_SCANCODE_UP;

	jump = false;
	right = false;
	left = false;

	moveSpeed = 300;

	cameraX = passCameraX;
	cameraY = passCameraY;

	cameraRect.x = positionRect.x + *cameraX;
	cameraRect.y = positionRect.y + *cameraY;
	cameraRect.w = positionRect.w;
	cameraRect.h = positionRect.h;
}

Shadow::~Shadow()
{
	SDL_DestroyTexture(shadow);
	shadow = NULL;	
}

//push object
void Shadow::push(Setting &sObject, const Uint8* keyState, float delta)
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
bool Shadow::action(const Uint8* keyState)
{
	if (keyState[keys[3]])
	{
		return true;
	}
	return false;
}
//get walking animation 
void Shadow::update(float delta, const Uint8* keyState)
{
	isActive = true; //set to true before every update
	//if player pressed left arrow
	if (keyState[keys[0]])
	{
		if (getOriginX() > 0 + *cameraX && getOriginX() > 600 + *cameraX && getOriginX() < GAME_WIDTH + *cameraX)
		{
			*cameraX = 600 - getOriginX();
			positionRect.x -= moveSpeed * delta;	
		}
		else
		{
			positionRect.x -= moveSpeed * delta;
		}
		
		cropRect.y = frameHeight; //set to frame height second row
		left = true;
		right = false;
	}
	//if player presses right arrow
	else if (keyState[keys[1]])
	{
		if (0 + getOriginX() > 600 + *cameraX && getOriginX() <  GAME_WIDTH + *cameraX)
		{
			positionRect.x += moveSpeed * delta;
			*cameraX = 600 - getOriginX();
		}
		else
		{
			positionRect.x += moveSpeed * delta;
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
		//if player does go past this height keep jumping
		if (positionRect.y > 250)
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
	if (airTime > 20 || !jump && positionRect.y < 400)
	{
		if (positionRect.y < 400)
		{
			isActive = false;
			positionRect.y += 15; 
		}
		if (positionRect.y == 400)
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
		cropRect.x = frameWidth;
	}
}

void Shadow::drawShadow(SDL_Renderer* renderTarget, float* cameraX)
{
	
	cameraRect.x = positionRect.x + *cameraX;
	cameraRect.y = positionRect.y + *cameraY;

	SDL_RenderCopy(renderTarget, shadow, &cropRect, &cameraRect);
}

void Shadow::resetShadow(SDL_Renderer* renderTarget)
{
	positionRect.x = 300;
	positionRect.y = 400;
	SDL_RenderCopy(renderTarget, shadow, &cropRect, &cameraRect);
}

void Shadow::fall()
{
	positionRect.y += 7;
}
bool Shadow::collide(Setting &sObject)
{
	//distance between two object
	distX = getOriginX() - sObject.getOriginX(); 
	distY = getOriginY() - sObject.getOriginY();
	//radius of both objects
	combRadius = radius + sObject.getRadius();
	//if distance x squared + distance y squared is less than the square
	//of the combined radius collision has occured
	if ((distX * distX) + (distY * distY) < combRadius * combRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Shadow::getOriginX()
{
	return positionRect.x + originX;
}

float Shadow::getOriginY()
{
	return positionRect.y + originY;
}

float Shadow::getRadius()
{
	return radius;
}
