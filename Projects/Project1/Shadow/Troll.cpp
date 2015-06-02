#include "Troll.h"
#include <stdio.h>
#include <iostream>


Troll::Troll(SDL_Renderer* gameRenderer, string filePath, int x, int y,
	int framesX, int framesY, float* passCameraX, float* passCameraY)
	: Monster(gameRenderer, filePath, x, y, framesX, framesY, passCameraX, passCameraY)
{
	startTroll = false;
	animateTimer = 0;
}
Troll::~Troll()
{
}

void Troll::attack(Troll &troll, Protagonist &player, Projectile &pebble,
	bool&gameOver, bool &hitTroll, bool &trollTrap, float delta)
{
	//check to see if player gets close to troll to start animation
	if (troll.getX() - 150 < player.getX() && !gameOver)
	{
		startTroll = true;
	}
	//check if player collides with troll
	if (troll.collide(player) && !gameOver)
	{
		gameOver = true;
	}
	//check if pebble gets close to troll to start animation
	if (troll.getX() - 150 < pebble.getX() && !trollTrap)
	{
		startTroll = true;
	}
	//check if pebble collides with troll
	if (troll.collide(pebble))
	{
		hitTroll = true;
	}
	if (startTroll)
	{
		if (cropRect.x < frameWidth * 7)
		{
			troll.animate(0.10f, delta, 0, startTroll);
		}
		if (cropRect.x == frameWidth * 7)
		{
			cropRect.x = frameWidth;
			startTroll = false;
		}
	}

}