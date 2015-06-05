#pragma once
#include <string>
#include "Monster.h"
#include "Projectile.h"

class Bird : public Monster
{
public:
	Bird(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int framesX, int framesY, float* passCameraX, float* passCameraY);
	~Bird();

	void move(float speed);
	void attack(Protagonist &player, Projectile &pebble, bool &gameOver, bool &hitBird);
	void scared(bool scaredB);

private:
	int birdCount;
	bool scaredBirds;


};
