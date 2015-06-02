#pragma once
#include <string>
#include "Setting.h"
#include "Shadow.h"

class Weapon : public Setting
{
public:
	Weapon(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int framesX, int framesY, float* passCameraX, float* passCameraY);
	~Weapon();

	void fire(int &pickUpTimer, bool &justPickedUp, bool &release, const Uint8* keyState);

protected:
	float fireSpeed;
	bool shootRight;
	bool shootLeft;
	bool fireWeapon;

private:
	SDL_Scancode keys[1];
	int pickUpTimer; //will be used to make sure shots aren't immediately fired upon picking up weapon

};
