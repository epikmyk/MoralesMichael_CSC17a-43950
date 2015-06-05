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

	originX = frameWidth / 2;
	originY = frameHeight / 2;
	radius = frameWidth * static_cast<float>(1) / 2;

	moveSpeed = 300;

	cameraX = passCameraX;
	cameraY = passCameraY;

	cameraRect.x = positionRect.x + *cameraX;
	cameraRect.y = positionRect.y + *cameraY;
	cameraRect.w = positionRect.w;
	cameraRect.h = positionRect.h;

	gameWidth = 15000;
}

Shadow::~Shadow()
{
	SDL_DestroyTexture(shadow);
	shadow = NULL;
}


//draw shadow to screen with camera
void Shadow::drawShadow(SDL_Renderer* gameRenderer, float* cameraX)
{
	cameraRect.x = positionRect.x + *cameraX;
	cameraRect.y = positionRect.y + *cameraY;

	SDL_RenderCopy(gameRenderer, shadow, &cropRect, &cameraRect);
}

//reset shadow position
void Shadow::resetShadow(SDL_Renderer* gameRenderer, int x, int y)
{
	cropRect.y = 0;
	positionRect.x = x;
	positionRect.y = y;
	SDL_RenderCopy(gameRenderer, shadow, &cropRect, &cameraRect);
}

//use to drop shadow
void Shadow::fall(int speed)
{
	if (positionRect.y < 720)
	{
		positionRect.y += speed;
	}
}

float Shadow::getY()
{
	return positionRect.y;
}

float Shadow::getX()
{
	return positionRect.x;
}

void Shadow::setY(float y)
{
	positionRect.y = y;
}

void Shadow::setX(float x)
{
	positionRect.x = x;
}

//get origin x for shadow
float Shadow::getOriginX()
{
	return positionRect.x + originX;
}

//get origin y for shadow
float Shadow::getOriginY()
{
	return positionRect.y + originY;
}

//get radius for shadow
float Shadow::getRadius()
{
	return radius;
}

float Shadow::getWidth()
{
	return positionRect.w;
}