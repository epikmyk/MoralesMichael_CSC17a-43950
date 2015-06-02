#pragma once

#include <string>
#include "Weapon.h"
#include "Protagonist.h"

class Projectile : public Weapon
{
public:
	Projectile(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int framesX, int framesY, float* passCameraX, float* passCameraY);
	~Projectile();

	void shoot(Projectile &bullet, Protagonist &shadow, bool &bulletHit,
		bool right, bool left);


private:
	int deathTimer;

};
