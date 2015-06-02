#include "Weapon.h"
#include <stdio.h>
#include <iostream>

Weapon::Weapon(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int framesX, int framesY, float* passCameraX, float* passCameraY)
	: Setting(gameRenderer, filePath, x, y, framesX, framesY, passCameraX, passCameraY)
{
	fireSpeed = 8;
	keys[0] = SDL_SCANCODE_UP;
	pickUpTimer = 0;
	shootRight = false;
	shootLeft = false;
	fireWeapon = false;
}

Weapon::~Weapon()
{
}

void Weapon::fire(int &pickUpTimer, bool &justPickedUp, bool &release, const Uint8* keyState)
{

	if (keyState[keys[0]] && pickUpTimer > 20)
	{
		release = true;
		justPickedUp = false;
	}

}