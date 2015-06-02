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
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	float getOriginX();
	float getOriginY();
	float getRadius();
	void moveRight(float speed);
	void moveLeft(float speed);
	void moveUp(float speed, int stoppingPoint);
	void resetSetting(int x, int y);
	void resetSettingY(int y);
	bool collide(Setting &sObject);

protected:
	SDL_Rect settingRect;

private:
	SDL_Renderer* gameRenderer;
	SDL_Texture* setting;
	int originX, originY;
	float radius;
	float* cameraX;
	float* cameraY;
	float distX, distY, combRadius; //distance x and y and combined radius
	SDL_Rect cameraRect;
};