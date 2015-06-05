#pragma once
#include <SDL.h>
#include <string>	
#include "Setting.h"

using namespace std;

class Shadow
{
public:
	Shadow(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int framesX, int framesY, float* passCameraX, float* passCameraY);
	~Shadow();

	void drawShadow(SDL_Renderer* gameRenderer, float* cameraX);
	void resetShadow(SDL_Renderer* gameRenderer, int x, int y);

	//bool collide(Shadow &sObject);
	void fall(int speed);

	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	float getOriginX();
	float getOriginY();
	float getRadius();
	float getWidth();

	virtual void move(float speed){};

	//collision detection
	template<class T>
	bool collide(T &sObject)
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

protected:
	float moveSpeed; //movement speed
	SDL_Rect positionRect; //rect for player position
	float* cameraX; //camera for x position
	float* cameraY; //camera for y position
	int gameWidth; // game width
	float frameCounter; //count frames for animation
	SDL_Rect cropRect; //cropped image
	int frameWidth, frameHeight; //frame width and height for cropped image
	int textureWidth; //width of image

private:
	SDL_Texture* shadow; //image
	float originX, originY, radius; //origin x and y and radius
	float distX, distY, combRadius; //distance x and y and combined radius
	SDL_Rect cameraRect; //rect for camera
};