#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "Menu.h"
#include "Setting.h"
#include "Shadow.h"

using namespace std;


const int LEVEL_WIDTH = 2400;
const int GAME_WIDTH = 4800;
int gameHeight = 720;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 720;

void newGame();

int main(int argc, char* args[])
{

	//initialize sdl
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "Could not initialize: " << SDL_GetError() << endl;
	}

	//initialize truetype fonts
	if (TTF_Init() < 0)
	{
		cout << "TTF could not initialize: " << TTF_GetError() << endl;
	}
	
	//initialize audio mix
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Could not load audio: " << Mix_GetError() << endl;
	}

	SDL_Window* gameWindow = NULL; //game window
	SDL_Renderer* gameRenderer = NULL; //renderer for game

	// create game window
	gameWindow = SDL_CreateWindow("Shadow", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (gameWindow == NULL)
	{
		cout << "Could not load window: " << SDL_GetError();
	}

	// creat game renderer
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC);

	if (gameRenderer == NULL)
	{
		cout << "Could not load renderer: " << SDL_GetError();
	}

	bool escapePressed = false; //determine if escape is pressed
	bool newGameSelected = true; //determine if new game is selected
	bool controlsSelected = false; //determine if controls is being selected
	bool controlScreen = false; //determine if control screen has been started
	bool upPressed = false; //determine if up is pressed
	bool downPressed = false; //determine if down is pressed
	bool enterPressed = false; //determine if entere is pressed
	bool gameStart = false; //determine if game has started
	bool gameRunning = true; //used to determing whether game is running
	bool pause = false; //determine if game is paused
	bool resumeSelected = false; //determine if resume has been selected
	bool deathTrap1 = false; //will determine if death trap has been activated
	bool trapDeactivate = false;
	bool gameOver = false;
	bool falling = false;
	bool bridgeUp = false;
	SDL_Event gameEvent; //game event 

	int currentTime = 0;
	int prevTime = 0;
	float delta = 0.0f;
	const Uint8* keyState;

	float cameraX = 0;
	float cameraY = 0;

	//background for menu
	Menu background(gameRenderer, "Images/shadowMenuBackG.png", 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	//new game button for menu
	Menu newGame(gameRenderer, "Images/shadowNewGame.png", 300, 400,
		300, 100);
	//new game button for menu when selecetd
	Menu selectNewGame(gameRenderer, "Images/shadowSelectNewGame.png", 300, 400,
		300, 100);
	//controls button for menu
	Menu controls(gameRenderer, "Images/shadowControls.png", 300, 480,
		300, 100);
	//controls button for menu is selected
	Menu selectControls(gameRenderer, "Images/shadowSelectControls.png", 300, 480,
		300, 100);
	//control screen menu
	Menu controlsMenu(gameRenderer, "Images/controlsMenu.png", 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	//resume button for pause menu
	Menu resume(gameRenderer, "Images/resume.png", 300, 400, 300, 100);
	//resume button for when resume is selected
	Menu selectResume(gameRenderer, "Images/selectResume.png", 300, 400, 300, 100);
	//background 1 for game setting
	Setting gameBackground1(gameRenderer, "Images/gameBackground1.png", 0, 0,
		LEVEL_WIDTH, SCREEN_HEIGHT, &cameraX, &cameraY);
	Setting gameBackground2(gameRenderer, "Images/gameBackground1.png", 2400, 0,
		LEVEL_WIDTH, SCREEN_HEIGHT, &cameraX, &cameraY);
	//ground
	Setting ground(gameRenderer, "Images/ground.png", 0, 570,
		LEVEL_WIDTH, 200, &cameraX, &cameraY);
	Setting bridge(gameRenderer, "Images/bridge.png", 2800, 570, 400, 90, &cameraX, &cameraY);
	Setting bridgeSwitch(gameRenderer, "Images/firstDeathTrap.png", 2250, 600,
		45, 35, &cameraX, &cameraY);
	Setting ground2(gameRenderer, "Images/ground.png", 2800, 570, LEVEL_WIDTH, 
		200, &cameraX, &cameraY);

	//tree 
	Setting tree(gameRenderer, "Images/tree.png", 800, -680, 800, 1300, 
		&cameraX, &cameraY);
	//death trap
	Setting firstDeathTrap(gameRenderer, "Images/firstDeathTrap.png", 1050, 600, 
		45, 35, &cameraX, &cameraY);
	//falling branch from death trap
	Setting killerRock(gameRenderer, "Images/rock.png", 950, -100, 140,
		110, &cameraX, &cameraY);
	//handle button for dropping rock
	Setting rockSwitch(gameRenderer, "Images/rockSwitch.png", 1225, 470, 25, 20,
		&cameraX, &cameraY);
	

	//main character named shadow
	Shadow shadow(gameRenderer, "Images/walkingAnimation.png", 300, 400, 5, 2,
		&cameraX, &cameraY);


	//gameloop
	while (gameRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		delta = (currentTime - prevTime) / 1000.0f;

		while (SDL_PollEvent(&gameEvent) != 0)
		{
			if (gameEvent.type == SDL_QUIT)
			{
				gameRunning = false;
			}
		}

		keyState = SDL_GetKeyboardState(NULL);

		SDL_RenderClear(gameRenderer);


		//Check to see if player has started game
		if (!(gameStart))
		{
			//draw background image
			background.drawMenu(gameRenderer);
			
			//if new game is selected
			if (newGameSelected)
			{
				//draw selected new game button
				selectNewGame.drawMenu(gameRenderer);
				//draw controls button
				controls.drawMenu(gameRenderer);
				//if s is pressed set controls selected to true
				if (downPressed)
				{
					controlsSelected = true;
					newGameSelected = false;
					downPressed = false;
				}
				if (enterPressed)
				{
					enterPressed = false;
					gameStart = true;	
				}
			}
			//if controls is selected
			if (controlsSelected)
			{
				//draw selected controls button
				selectControls.drawMenu(gameRenderer);
				//draw new game button
				newGame.drawMenu(gameRenderer);
				//if w is pressed set new game selected to true
				if (upPressed)
				{
					newGameSelected = true;
					controlsSelected = false;
					upPressed = false;
				}
				//if enter is pressed go set control screen to true
				if (enterPressed)
				{
					newGameSelected = false;
					enterPressed = false;
					controlsSelected = true;
					controlScreen = true;
				}
			}

			//if control screen is open
			if (controlScreen)
			{
				//draw control screen
				controlsMenu.drawMenu(gameRenderer);
				if (gameEvent.type == SDL_KEYDOWN)
				{
					switch (gameEvent.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						controlsSelected = true;
						controlScreen = false;
						escapePressed = true;
						break;
					default:
						break;
					}
				}
			}

			//Check which key is pressed
			if (gameEvent.type == SDL_KEYDOWN)
			{
				switch (gameEvent.key.keysym.sym)
				{
				case SDLK_RETURN:
					enterPressed = true;
					break;
				case SDLK_UP:
					upPressed = true;
					downPressed = false;
					break;
				case SDLK_DOWN:
					downPressed = true;
					upPressed = false;
					break;
				default:
					break;
				}
			}	
		}
		///////////////////////
		//IF GAME HAS STARTED//
		if (gameStart)
		{
			//draw background setting
			gameBackground1.drawSetting(gameRenderer, &cameraX);
			gameBackground2.drawSetting(gameRenderer, &cameraX);
			bridge.drawSetting(gameRenderer, &cameraX);
			ground.drawSetting(gameRenderer, &cameraX);
			ground2.drawSetting(gameRenderer, &cameraX);
			bridgeSwitch.drawSetting(gameRenderer, &cameraX);
			//draw tree
			tree.drawSetting(gameRenderer, &cameraX);
			//draw first death trap
			rockSwitch.drawSetting(gameRenderer, &cameraX);
			firstDeathTrap.drawSetting(gameRenderer, &cameraX);
			//draw rock
			killerRock.drawSetting(gameRenderer, &cameraX);

			if (!pause && !gameOver && !falling)
			{
				//get shadow movement/animation
				shadow.update(delta, keyState);	
			}
			
			if (!gameOver)
			{
				//draw shadow character
				shadow.drawShadow(gameRenderer, &cameraX);
			}

			//determine if player walks into death trap
			if (shadow.collide(firstDeathTrap))
			{
				deathTrap1 = true; //set falling branch to true
			}

			//if death trap has been activated
			if (deathTrap1)
			{
				if (!pause)
				{
					//drop rock
					killerRock.fallFromSky(530, 15);
				}
			}

			//if rock falls on shadow, shadow dead
			if (shadow.collide(killerRock) && killerRock.getOriginY() - 55 < 530
				&& !trapDeactivate)
			{
				resumeSelected = true;
				gameOver = true;
				enterPressed = false;
			}
			//if switch is pressed then drop rock
			if (shadow.collide(rockSwitch) && shadow.action(keyState))
			{
				trapDeactivate = true;
			}
			if (trapDeactivate)
			{
				killerRock.fallFromSky(530, 15);
			}

			//if shadow grabs rock get push action
			if (shadow.collide(killerRock) && shadow.action(keyState) &&
				killerRock.getOriginY() - 55 == 530)
			{
				shadow.push(killerRock, keyState, delta);
			}
			
			//if shadow steps on bridge switch
			if (shadow.collide(bridgeSwitch) || killerRock.collide(bridgeSwitch))
			{
				bridgeUp = true;
				if (bridge.getOriginX() - 200 != ground.getOriginX() * 2)
				{
					bridge.moveLeft(5);
				}
			}

			
			if (!shadow.collide(bridgeSwitch) && !killerRock.collide(bridgeSwitch))
			{
				bridgeUp = false;
				if (bridge.getOriginX() - 200 != 2800)
				{
					bridge.moveRight(5);
				}
			}
			
			//determing of shadow walks off ledge
			if (shadow.getOriginX() > ground.getOriginX() * 2 && shadow.getOriginY() >= 500 && !bridgeUp)
			{
				shadow.fall();
				falling = true;
			}
			//if shadow falls game over
			if (shadow.getOriginY() > SCREEN_HEIGHT)
			{
				gameOver = true;
			}

			resumeSelected = true;

			//determine if game is paused
			if (gameEvent.type == SDL_KEYDOWN)
			{
				switch (gameEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					pause = true;
					escapePressed = true;
					break;
				default:
					break;
				}
			}

			if (pause)
			{
				//Check which key is pressed
				if (gameEvent.type == SDL_KEYDOWN)
				{
					switch (gameEvent.key.keysym.sym)
					{
					case SDLK_RETURN:
						enterPressed = true;
						break;
					case SDLK_UP:
						upPressed = true;
						downPressed = false;
						break;
					case SDLK_DOWN:
						downPressed = true;
						upPressed = false;
						break;
					default:
						break;
					}
				}

				//if resume is selected
				if (resumeSelected && !controlsSelected)
				{
					//draw selected resume button
					selectResume.drawMenu(gameRenderer);
					//draw controls button
					controls.drawMenu(gameRenderer);
					//if s is pressed set controls selected to true
					if (downPressed)
					{
						controlsSelected = true;
						resumeSelected = false;
						downPressed = false;
					}
					if (enterPressed)
					{
						enterPressed = false;
						pause = false;
					}
				}
				//if controls is selected
				if (controlsSelected)
				{
					//draw selected controls button
					selectControls.drawMenu(gameRenderer);
					//draw resume button
					resume.drawMenu(gameRenderer);
					//if up is pressed set new game selected to true
					if (upPressed)
					{
						resumeSelected = true;
						controlsSelected = false;
						upPressed = false;
					}
					//if enter is pressed go set control screen to true
					if (enterPressed)
					{
						resumeSelected = false;
						enterPressed = false;
						controlsSelected = true;
						controlScreen = true;
					}
				}

				//if control screen is open
				if (controlScreen)
				{
					//draw control screen
					controlsMenu.drawMenu(gameRenderer);
					if (gameEvent.type == SDL_KEYDOWN)
					{
						switch (gameEvent.key.keysym.sym)
						{
						case SDLK_ESCAPE:
							controlsSelected = true;
							controlScreen = false;
							escapePressed = true;
							break;
						default:
							break;
						}
					}
				}	
			}
		}
		////////////////
		////GAME OVER///
		if (gameOver)
		{
			trapDeactivate = false;
			//Check which key is pressed
			if (gameEvent.type == SDL_KEYDOWN)
			{
				switch (gameEvent.key.keysym.sym)
				{
				case SDLK_RETURN:
					enterPressed = true;
					break;
				case SDLK_UP:
					upPressed = true;
					downPressed = false;
					break;
				case SDLK_DOWN:
					downPressed = true;
					upPressed = false;
					break;
				default:
					break;
				}
			}
			falling = false;
			
			//if resume is selected
			if (resumeSelected && !controlsSelected)
			{
				//draw selected resume button
				selectResume.drawMenu(gameRenderer);
				//draw controls button
				controls.drawMenu(gameRenderer);
				
				if (downPressed)
				{
					controlsSelected = true;
					resumeSelected = false;
					downPressed = false;
				}
				if (enterPressed)
				{
					cameraX = 0;
					cameraY = 0;
					shadow.resetShadow(gameRenderer);
					killerRock.resetSetting(950, -100);
					deathTrap1 = false;
					enterPressed = false;
					gameOver = false;
				}
			}
			//if controls is selected
			if (controlsSelected)
			{
				//draw selected controls button
				selectControls.drawMenu(gameRenderer);
				//draw resume button
				resume.drawMenu(gameRenderer);
				//if up is pressed set new game selected to true
				if (upPressed)
				{
					resumeSelected = true;
					controlsSelected = false;
					upPressed = false;
				}
				//if enter is pressed go set control screen to true
				if (enterPressed)
				{
					resumeSelected = false;
					enterPressed = false;
					controlsSelected = true;
					controlScreen = true;
				}
			}

			//if control screen is open
			if (controlScreen)
			{
				//draw control screen
				controlsMenu.drawMenu(gameRenderer);
				if (gameEvent.type == SDL_KEYDOWN)
				{
					switch (gameEvent.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						controlsSelected = true;
						controlScreen = false;
						escapePressed = true;
						break;
					default:
						break;
					}
				}
			}
		}
		
		SDL_RenderPresent(gameRenderer);		
	}

	//deallocate memory
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = NULL;

	SDL_Quit();
	IMG_Quit();

	return 0;
}

void newGame(bool &newGameSelected, bool &controlsSelected, bool &downPressed,
	bool &enterPressed, bool gameStart, Menu selectNewGame, Menu controls,
	SDL_Renderer* gameRenderer)
{
	//if new game is selected
	if (newGameSelected)
	{
		//draw selected new game button
		selectNewGame.drawMenu(gameRenderer);
		//draw controls button
		controls.drawMenu(gameRenderer);
		//if s is pressed set controls selected to true
		if (downPressed)
		{
			controlsSelected = true;
			newGameSelected = false;
			downPressed = false;
		}
		if (enterPressed)
		{
			enterPressed = false;
			gameStart = true;
		}
	}
}