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

	void update(float delta, const Uint8* keyState);
	void drawShadow(SDL_Renderer* gameRenderer, float* cameraX);
	void resetShadow(SDL_Renderer* renderTarget);
	bool collide(Setting &sObject);
	bool action(const Uint8* keyState);
	void push(Setting &sObject, const Uint8* keyState, float delta);
	void jumping(const Uint8* keyState);
	void fall();

	float getOriginX(); 
	float getOriginY();
	float getRadius();

	const int GAME_WIDTH = 4800;

private:
	SDL_Rect cropRect; //cropped image
	SDL_Texture* shadow; //sprite sheet for shadow image
	float moveSpeed; //movement speed
	float frameCounter; //count frames for animation
	int frameWidth, frameHeight; //frame width and height for cropped image
	int textureWidth; //width of image
	float originX, originY, radius; //origin x and y and radius
	float distX, distY, combRadius; //distance x and y and combined radius
	bool isActive; //used if animation is occuring
	SDL_Scancode keys[4]; //keys to be used 
	int airTime; //air time for jump
	bool jump, right, left;
	float* cameraX;
	float* cameraY;
	SDL_Rect cameraRect;

	SDL_Rect positionRect;
};

