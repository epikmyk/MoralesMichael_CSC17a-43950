#pragma once
#include <SDL.h>
#include <string>
using namespace std;

class Setting
{
public:
	Setting(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int w, int h, float* passCameraX, float* passCameraY);
	~Setting();

	void drawSetting(SDL_Renderer* gameRenderer, float* cameraX);
	void fallFromSky(int groundBound, int fallSpeed);
	float getOriginX();
	float getOriginY();
	float getRadius();
	void moveRight(float speed);
	void moveLeft(float speed);
	void resetSetting(int x, int y);
	bool collide(Setting &sObject);

private:
	SDL_Renderer* gameRenderer;
	SDL_Texture* setting;
	SDL_Rect settingRect;
	int originX, originY;
	float radius;
	float* cameraX;
	float* cameraY;
	float distX, distY, combRadius; //distance x and y and combined radius
	SDL_Rect cameraRect;
};

