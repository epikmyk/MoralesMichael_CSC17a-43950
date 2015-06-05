#include "Projectile.h"
#include <stdio.h>
#include <iostream>

Projectile::Projectile(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int framesX, int framesY, float* passCameraX, float* passCameraY)
	: Weapon(gameRenderer, filePath, x, y, framesX, framesY, passCameraX, passCameraY)
{

}

Projectile::~Projectile()
{
}

//shoot projectile
void Projectile::shoot(Projectile &bullet, Protagonist &shadow, 
	bool &bulletHit, bool right, bool left)
{
	//if facing right shoot right
	if (right && !shootLeft)
	{
		shootRight = true;
		shootLeft = false;
	}
	//if facing left shoot left
	if (left && !shootRight)
	{
		shootLeft = true;
		shootRight = false;
	}
	//shoot to right
	if (shootRight && !shootLeft)
	{
		//move bullet if bullet hit is false
		//bullet hit is used to detect if bullet hits something
		if (!bulletHit)
		{
			settingRect.x += fireSpeed;
		}
		//if bullet goes passed screen
		if (bullet.getOriginX() > shadow.getOriginX() + 600)
		{
			shootRight = false;
		}
		//if bullet goes passed screen
		if (bullet.getOriginX() < shadow.getOriginX() - 600)
		{
			shootRight = false;
			bulletHit = false;
		}
	}
	//shoot to left
	if (shootLeft && !shootRight)
	{
		//move bullet if bullet hit is false
		//bullet hit is used to detect if bullet hits something
		if (!bulletHit)
		{
			settingRect.x -= fireSpeed;
		}
		//if bullet goes passed screen
		if (bullet.getOriginX() < shadow.getOriginX() - 600)
		{
			shootLeft = false;
		}
		//if bullet goes passed screen
		if (bullet.getOriginX() > shadow.getOriginX() + 600)
		{
			shootLeft = false;
	        bulletHit = false;
		}
	}
}