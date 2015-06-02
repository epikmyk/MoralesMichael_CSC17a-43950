#pragma once
#include <SDL.h>
#include <string>
#include "Shadow.h"
#include "Weapon.h"

class Protagonist : public Shadow
{
public:
	Protagonist(SDL_Renderer* gameRenderer, string filePath, int x, int y,
		int framesX, int framesY, float* passCameraX, float* passCameraY);
	~Protagonist();

	void update(float delta, const Uint8* keyState, bool fall, bool &right, bool &left);
	bool action(const Uint8* keyState);
	void push(Setting &sObject, const Uint8* keyState, float delta);
	void jumping(const Uint8* keyState);
	void carry(Weapon &weap, const Uint8* keyState, bool right, bool left);
	void drop(Weapon &weap, const Uint8* keyState, bool &carry);

private:
	SDL_Scancode keys[5]; //keys to be used
	int airTime; //air time for jump
	bool jump; //determine if jumping
	bool isActive; //used if animation is occuring
};


