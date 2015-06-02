#pragma once
#include <string>
#include "Monster.h"
#include "Protagonist.h"
#include "Projectile.h"

class Troll : public Monster
{
public:
	Troll(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int framesX, int framesY, float* passCameraX, float* passCameraY);
	~Troll();

	void attack(Troll &troll, Protagonist &player, Projectile &pebble, 
		bool &gameOver, bool &hitTroll, bool &trollTrap, float delta);


private:
	bool startTroll;
	int animateTimer;
};
