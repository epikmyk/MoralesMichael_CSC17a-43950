#include "Setting.h"
#include <SDL_image.h>
#include <iostream>

Setting::Setting(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int w, int h, float* passCameraX, float* passCameraY)
{
	setting = NULL;
	//load image texture for setting object
	setting = IMG_LoadTexture(gameRenderer, filePath.c_str());

	if (setting == NULL)
	{
		cout << "could not load image: " << IMG_GetError();
	}

	settingRect.x = x; //x position of image
	settingRect.y = y; //y position of image
	settingRect.w = w; //width of image
	settingRect.h = h; //height of image

	originX = settingRect.w / 2;
	originY = settingRect.h / 2;
	radius = settingRect.w * static_cast<float>(1) / 2;

	cameraX = passCameraX;
	cameraY = passCameraY;

	cameraRect.x = settingRect.x + *cameraX;
	cameraRect.y = settingRect.y + *cameraY;
	cameraRect.w = settingRect.w;
	cameraRect.h = settingRect.h;

}

Setting::~Setting()
{
	SDL_DestroyTexture(setting);
	setting = NULL;
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = NULL;
}

//drop object from sky
void Setting::fallFromSky(int groundBound, int fallSpeed)
{
	if (settingRect.y < groundBound)
	{
		settingRect.y += fallSpeed;
	}
}

void Setting::moveUp(float speed, int stoppingPoint)
{
	if (settingRect.y > stoppingPoint)
	{
		settingRect.y -= speed;
	}
}
void Setting::moveRight(float speed)
{
	settingRect.x += speed;
}

void Setting::moveLeft(float speed)
{
	if (settingRect.x > 0)
	{
		settingRect.x -= speed;
	}
}

bool Setting::collide(Setting &sObject)
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

//draw to screen
void Setting::drawSetting(SDL_Renderer* gameRenderer, float* cameraX)
{

	cameraRect.x = settingRect.x + *cameraX;
	cameraRect.y = settingRect.y + *cameraY;

	SDL_RenderCopy(gameRenderer, setting, NULL, &cameraRect);
}

//reset both x and y position
void Setting::resetSetting(int x, int y)
{
	settingRect.x = x;
	settingRect.y = y;
}

//reset y position
void Setting::resetSettingY(int y)
{
	settingRect.y = y;
}

float Setting::getOriginX()
{
	return settingRect.x + originX;
}

float Setting::getOriginY()
{
	return settingRect.y + originY;
}

float Setting::getRadius()
{
	return radius;
}

void Setting::setX(float x)
{
	settingRect.x = x;
}

void Setting::setY(float y)
{
	settingRect.y = y;
}

float Setting::getX()
{
	return settingRect.x;
}

float Setting::getY()
{
	return settingRect.y;
}