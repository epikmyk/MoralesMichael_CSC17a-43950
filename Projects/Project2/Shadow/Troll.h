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
	void move(float speed);
	
private:
	bool startTroll; // determine if troll animation should start
	int animateTimer; //determine how long to animate
};
