/*things to change: 
-shorten code for saving and in general. too much repeating for resetting values, 
but didn't have enough time to shorten.
-should probably put ground into some sort of array
-try and get user input text in game window instead of console
-already sort of created a text class but haven't figure out how to
get it to work with user input. 
-add sound
-game itself is not complete. this can be thought of as a demo.
-*/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Menu.h"
#include "Setting.h"
#include "Shadow.h"
#include "Text.h"

using namespace std;

struct SaveInfo
{
	int savePoint;
	char playerName[15];
};

void copyToFile(string, SaveInfo);

int main(int argc, char* args[])
{
	const int LEVEL_WIDTH = 2400;
	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 720;

	SaveInfo saving;

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
	bool downPressed = false; //determine if down is pressed
	bool upPressed = false; //determine if up is pressed
	bool enterPressed = false; //determine if entere is pressed
	bool mainMenuSelected = false; //determine if main meny is selected
	bool continueSelected = false; //determine if continue is selected for menu
	bool newGameSelected = false; //determine if new game is selected
	bool resumeSelected = false; //determine if resume has been selected
	bool controlsSelected = false; //determine if controls is being selected
	bool controlScreen = false; //determine if control screen has been started
	bool mainMenuScreen = true; //if main menu screen is up
	bool newGameStarted; //will determine if new game has been loaded
	bool gameStart = false; //determine if game has started
	bool gameRunning = true; //used to determing whether game is running
	bool pause = false; //determine if game is paused
	bool deathTrap1 = false; //will determine if death trap has been activated
	bool trapDeactivate = false; //if trap is activated
	bool gameOver = false; //will determine of game is over
	bool falling = false; //will determine of object is falling
	bool bridgeUp = false; //will determine of bridge is up
	bool bridgeLocksUp = false; //detmine if birdge stays up
	bool startDog = false; //will determine if dog animation starts
	bool deadDog = false; //will determine if dog dies
	bool pushing = false; //determine if player is pushing object
	bool bridgeMoving = false; //determine if bridge is moving
	bool actionPressed = false; //determine if player has pressed action button
	bool enterName = false; //determine if player has entered name
	bool rockBridge = false; //determine if rock bridge
	bool enterPass = false; //determine if user has been prompted to enter password
	bool correctPass = true; //if user enteres correctly
	bool doorUp = false; //will determine if door is up or down
	SDL_Event gameEvent;

	int currentTime = 0;
	int prevTime = 0;
	float delta = 0.0f; 
	const Uint8* keyState;

	//int timer = 0; 
	int charPos = 0; //determines character postion
	int count = 0; //count for when user enters password
	char doorPass[15]; //password that user enters to get passed door
	saving.playerName[15]; //player name and also password!

	float cameraX = 0; //camerax position
	float cameraY = 0; //cameray position

	//background for menu
	Menu background(gameRenderer, "Images/shadowMenuBackG.png", 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	Menu continueGame(gameRenderer, "Images/continue.png", 300, 320, 300, 100);
	Menu selectContinueGame(gameRenderer, "Images/selectContinue.png", 300, 320, 300, 100);
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
	//main menu button
	Menu mainMenu(gameRenderer, "Images/mainMenu.png", 300, 480, 300, 100);
	//main meny button is selected
	Menu selectMainMenu(gameRenderer, "Images/selectMainMenu.png", 300, 480, 300, 100);
	//resume button for pause menu
	Menu resume(gameRenderer, "Images/resume.png", 300, 400, 300, 100);
	//resume button for when resume is selected
	Menu selectResume(gameRenderer, "Images/selectResume.png", 300, 400, 300, 100);
	Setting* gameBackground[4]; //array for background setting
	int backgroundWidth = 0; //set to 0
	for (int i = 0; i < 4; i++)
	{
		//fill game background to game width
		gameBackground[i] = new Setting(gameRenderer, "Images/gameBackground1.png",
			backgroundWidth, 0, LEVEL_WIDTH, SCREEN_HEIGHT, &cameraX, &cameraY);
		    backgroundWidth += LEVEL_WIDTH;
	}
	//ground
	Setting ground(gameRenderer, "Images/ground.png", 0, 570,
		LEVEL_WIDTH, 200, &cameraX, &cameraY);
	Setting ground2(gameRenderer, "Images/ground.png", 2800, 570, LEVEL_WIDTH - 400,
		200, &cameraX, &cameraY);
	Setting ground3(gameRenderer, "Images/ground.png", 5450, 570, LEVEL_WIDTH - 400,
		200, &cameraX, &cameraY);
	Setting ground4(gameRenderer, "Images/ground.png", 7450, 570, LEVEL_WIDTH - 400,
		200, &cameraX, &cameraY);
	//bridge
	Setting bridge(gameRenderer, "Images/bridge.png", 2800, 570, 400, 90, &cameraX, &cameraY);
	//switch to activate bridge
	Setting bridgeSwitch(gameRenderer, "Images/firstDeathTrap.png", 2250, 600,
		45, 35, &cameraX, &cameraY);
	Setting bridgeLever(gameRenderer, "Images/rockSwitch.png", 2800, 580, 30, 25, &cameraX, &cameraY);
	//create array for bridge lock object
	Setting* bridgeLock[2];
	int bridgeLockPos = 0;
	for (int i = 0; i < 2; i++)
	{
		bridgeLock[i] = new Setting(gameRenderer, "Images/bridgeLock.png", 2400 + bridgeLockPos,
			570, 20, 90, &cameraX, &cameraY);
		bridgeLockPos += 380;
	}
	//tree
	Setting tree(gameRenderer, "Images/tree.png", 800, -680, 800, 1300,
		&cameraX, &cameraY);
	//death trap
	Setting firstDeathTrap(gameRenderer, "Images/firstDeathTrap.png", 1050, 600,
		45, 35, &cameraX, &cameraY);
	//falling rock from death trap
	Setting killerRock(gameRenderer, "Images/rock.png", 950, -100, 170,
		120, &cameraX, &cameraY);
	Setting* bridgeOfrocks[3];
	int rockPosX = 0;
	int rockPosY = 0; 
	//array for bridge of rocks
	//rock position will determine wherer they are located
	for (int i = 0; i < 3; i++)
	{
		bridgeOfrocks[i] = new Setting(gameRenderer, "Images/rock.png", 4950 + rockPosX,
			-120 - rockPosY, 170, 120, &cameraX, &cameraY);
		rockPosX += 170;
		rockPosY += 700;
	}
	//handle button for dropping rock
	Setting rockSwitch(gameRenderer, "Images/rockSwitch.png", 1225, 510, 30, 25,
		&cameraX, &cameraY);
	//Bushes that will hid killer dog
	Setting bush1(gameRenderer, "Images/bush.png", 3700, 350, 400, 304,
		&cameraX, &cameraY);
	Setting bush2(gameRenderer, "Images/bush.png", 3900, 350, 400, 304,
		&cameraX, &cameraY);
	//spike trap
	Setting spikeTrap(gameRenderer, "Images/spikeTrap.png", 4800, SCREEN_HEIGHT - 30,
		690, 40, &cameraX, &cameraY);
	Setting door(gameRenderer, "Images/door.png", 7000, 0, 345, 720, &cameraX, &cameraY);
	Setting sign(gameRenderer, "Images/sign.png", 6400, 410, 200, 200, &cameraX, &cameraY);

	//main character named shadow
	Shadow shadow(gameRenderer, "Images/shadow.png", 300, 500, 9, 2,
		&cameraX, &cameraY);
	//main character named shadow
	Shadow killerDog(gameRenderer, "Images/killerDog.png", 3950, 520, 5, 2,
		&cameraX, &cameraY);
	Text* playerNameInp = NULL;
	
	saving.savePoint = 0;
	string fileName = "gameSave";
	fstream file;

	//open file for reading
	file.open(fileName.c_str(), ios::in | ios::binary);
	if (file.fail())
	{
		file.open(fileName.c_str(), ios::out | ios::binary);
		cout << "creating new file" << endl;
	}
	else
	{
		//read file
		file.read(reinterpret_cast<char *>(&saving), sizeof(saving));
		cout << "game save loaded: " << endl;
		cout << "save point: " << saving.savePoint << endl;
		//close file
		file.close();
	}
	file.close();
	

	//if saving point is at least 1
	if (saving.savePoint >= 1)
	{
		continueSelected = true;
	}
	else
	{
		newGameSelected = true;
	}

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
		if (gameStart == false)
		{
			if (mainMenuScreen)
			{
				//draw background image
				background.drawMenu(gameRenderer);
				//if return key is released
				if (gameEvent.type == SDL_KEYUP)
				{
					switch (gameEvent.key.keysym.sym)
					{
					case SDLK_RETURN:
						enterPressed = false;
						break;
					case SDLK_UP:
						upPressed = false;
					case SDLK_DOWN:
						downPressed = false;
					default:
						break;
					}
				}
				//if continue is selected
				if (continueSelected && !enterPressed &&!newGameSelected)
				{
					selectContinueGame.drawMenu(gameRenderer);
					//draw new game button
					newGame.drawMenu(gameRenderer);
					//draw controls button
					controls.drawMenu(gameRenderer);
					
					if (gameEvent.type == SDL_KEYDOWN)
					{
						switch (gameEvent.key.keysym.sym)
						{
						case SDLK_RETURN:
							if (saving.savePoint >= 1)
							{
								shadow.resetShadow(gameRenderer, 4700, 500);
								//reset camera
								cameraX = -shadow.getOriginX() + SCREEN_WIDTH / 2;
								killerDog.resetShadow(gameRenderer, 3950, 750);
								killerRock.resetSetting(4800, 600);
								bridgeLever.resetSetting(2800, 580);
								for (int i = 0; i < 3; i++)
								{
									bridgeOfrocks[i]->resetSetting(4450 + rockPosX, 600);
									rockPosX += 170;
								}
								bridge.resetSetting(2400, 570);
								bridgeLever.resetSettingY(550);
								bridgeUp = true;
								rockBridge = true;
								deathTrap1 = true;
								bridgeLocksUp = true;
								deadDog = true;
								doorUp = false;
							}
							gameStart = true;
							enterPressed = true;
							mainMenuScreen = false;
							break;
						case SDLK_DOWN:
							newGameSelected = true;
							continueSelected = false;
							downPressed = true;
							continueSelected = false;
							break;
						default:
							break;
						}
					}
				}
				//if new game is selected
				if (newGameSelected && !enterPressed && !controlsSelected 
					&& !continueSelected)
				{
					if (saving.savePoint >= 1)
					{
						//draw continue game button
						continueGame.drawMenu(gameRenderer);
					}
					//draw selected new game button
					selectNewGame.drawMenu(gameRenderer);
					//draw controls button
					controls.drawMenu(gameRenderer);
					//make sure down isnt already pressed otherwise keyboard
					//constantly registers press and it skips from continue
					//straight to control
					if (!downPressed)
					{
						if (gameEvent.type == SDL_KEYDOWN)
						{
							switch (gameEvent.key.keysym.sym)
							{
							case SDLK_RETURN:
								enterName = true;
								//gameStart = true;
								saving.savePoint = 0;
								copyToFile(fileName, saving);
								enterPressed = true;
								mainMenuScreen = false;
								break;
							case SDLK_DOWN:
								controlsSelected = true;
								newGameSelected = false;
								continueSelected = false;
								downPressed = true;
								break;
							default:
								break;
							}
						}
					}
					if (saving.savePoint >= 1)
					{
						//make sure up isnt already pressed otherwise keyboard
						//constantly registers press and it skips from control
						//straight to continue
						if (!upPressed)
						{
							if (gameEvent.type == SDL_KEYDOWN)
							{
								switch (gameEvent.key.keysym.sym)
								{
								case SDLK_UP:
									upPressed = true;
									newGameSelected = false;
									continueSelected = true;
									break;
								}
							}
						}
					}
				}

				//prompt user to enter name for save file
				if (enterName)
				{
					cout << "Max characters: 15" << endl;
					cout << "Enter name: ";
					cin.getline(saving.playerName, 15);
					
					if (gameEvent.type == SDL_KEYDOWN)
					{
						switch (gameEvent.key.keysym.sym)
						{
						case SDLK_RETURN:
							gameStart = true;
							enterPressed = true;
							mainMenuScreen = false;
							enterName = false;
							break;
						default:
							break;
						}
					}
				}
				//if controls is selected
				if (controlsSelected && !enterPressed && !newGameSelected)
				{
					if (saving.savePoint >= 1)
					{
						//draw continue game button
						continueGame.drawMenu(gameRenderer);
					}
					//draw selected controls button
					selectControls.drawMenu(gameRenderer);
					//draw new game button
					newGame.drawMenu(gameRenderer);
					//if up is pressed set new game selected to true
					if (gameEvent.type == SDL_KEYDOWN)
					{
						switch (gameEvent.key.keysym.sym)
						{
						case SDLK_RETURN:
							controlsSelected = true;
							controlScreen = true;
							enterPressed = true;
							break;
						case SDLK_UP:
							newGameSelected = true;
							upPressed = true;
							controlsSelected = false;
							continueSelected = false;
							break;
						default:
							break;
						}
					}
				}

				//if control screen is open
				if (controlScreen)
				{
					controlsMenu.drawMenu(gameRenderer);
					if (gameEvent.type == SDL_KEYDOWN)
					{
						switch (gameEvent.key.keysym.sym)
						{
						case SDLK_ESCAPE:
							controlsSelected = true;
							controlScreen = false;
							break;
						default:
							break;
						}
					}
				}
			}
		}
		///////////////////////
		//IF GAME HAS STARTED//
		if (gameStart)
		{

			if (!mainMenuScreen)
			{
				//draw background settings
				for (int i = 0; i < 4; i++)
				{
					gameBackground[i]->drawSetting(gameRenderer, &cameraX);
				}
				for (int i = 0; i < 3; i++)
				{
					bridgeOfrocks[i]->drawSetting(gameRenderer, &cameraX);
				}
				//draw bridge
				bridge.drawSetting(gameRenderer, &cameraX);
				//draw bridge lever past bridge
				bridgeLever.drawSetting(gameRenderer, &cameraX);
				//draw ground
				ground.drawSetting(gameRenderer, &cameraX);
				ground2.drawSetting(gameRenderer, &cameraX);
				ground3.drawSetting(gameRenderer, &cameraX);
				ground4.drawSetting(gameRenderer, &cameraX);
				//draw bridge lever past bridge
				bush1.drawSetting(gameRenderer, &cameraX);
				//draw dog
				killerDog.drawShadow(gameRenderer, &cameraX);
				//draw bush
				bush2.drawSetting(gameRenderer, &cameraX);
				//draw bridge switch
				bridgeSwitch.drawSetting(gameRenderer, &cameraX);
				//draw tree
				tree.drawSetting(gameRenderer, &cameraX);
				//draw switch to drop rock
				rockSwitch.drawSetting(gameRenderer, &cameraX);
				//draw first death trap
				firstDeathTrap.drawSetting(gameRenderer, &cameraX);
				//draw rock
				killerRock.drawSetting(gameRenderer, &cameraX);
				//draw spikes
				spikeTrap.drawSetting(gameRenderer, &cameraX);
				//draw door exit to finish game
				door.drawSetting(gameRenderer, &cameraX);
				sign.drawSetting(gameRenderer, &cameraX);

			}

			//game is not paused and game is not over and character isnt falling
			if (!pause && !gameOver)
			{
				//get shadow movement/animation
				shadow.update(delta, keyState, falling);
			}

			//if game is not over
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
					killerRock.fallFromSky(530, 18);
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
			//if trap is deactivated drop rock
			if (trapDeactivate)
			{
				killerRock.fallFromSky(530, 18);
			}

			//if shadow grabs rock get push action
			if (shadow.collide(killerRock) && shadow.action(keyState) &&
				killerRock.getOriginY() == 530 + 60 && !pause)
			{
				pushing = true;
				shadow.push(killerRock, keyState, delta);
			}
			else
			{
				pushing = false;
			}

			//if player steps on bridge or places rock on bridge switch
			if (shadow.collide(bridgeSwitch) || killerRock.collide(bridgeSwitch))
			{
				//set bridg up to true
				bridgeUp = true;
				//move bridge left until it reachs stop point
				if (bridge.getOriginX() - 200 != ground.getOriginX() * 2 && !pause)
				{
					bridge.moveLeft(5);
				}
			}

			if (!shadow.collide(bridgeSwitch) && !killerRock.collide(bridgeSwitch))
			{
				//set bridge up to false
				bridgeUp = false;
				//move bridge right until it reaches stop point
				if (bridge.getOriginX() - 200 != 2800 && !pause && !bridgeLocksUp)
				{
					bridge.moveRight(5);
				}
			}

			//this will permanently keep the bridge up
			//the main purpose of this is to bring the rock over the bridge
			//in a nice easy manner and if the player pushes rock off edge
			//from the right side of the bridge they will be able to go back
			//and press the rock switch to get it back since the rock will
			//be needed one more time
			if (shadow.collide(bridgeLever) && shadow.getOriginX() >= 2400
				&& !pushing && deadDog)
			{
				if (shadow.action(keyState))
				{
					actionPressed = true;
					bridgeLocksUp = true;
				}
				if (actionPressed && bridge.getOriginX() - 200 != ground.getOriginX() * 2
					&& !pause)
				{
					bridge.moveLeft(5); //move bridge to left
				}
				if (bridge.getOriginX() - 200 == ground.getOriginX() * 2)
				{
					actionPressed = false;
				}
				bridgeUp = true; 
			}
			//if bridge locks are up draw bridge locks to screen
			if (bridgeLocksUp)
			{
				bridgeUp = true;
				bridgeLock[0]->drawSetting(gameRenderer, &cameraX);
				bridgeLock[1]->drawSetting(gameRenderer, &cameraX);
			}

			//if shadow falls game over
			if (shadow.getOriginY() > SCREEN_HEIGHT)
			{
				gameOver = true;
			}

			//determine if player walks near bush
			if (shadow.collide(bush1))
			{
				startDog = true;
			}
			//start dog animation
			if (startDog && !pause && !gameOver)
			{
				killerDog.animate(delta, 5, 0, startDog);
			}
			//if killer dog gets to this point and bridge is down dog will fall and die
			if (killerDog.getOriginX() < 2800 && !bridgeUp && !killerDog.collide(bridge))
			{
				startDog = false;
				deadDog = true;
				killerDog.fall(7);
			}
			//if player goes back past bridge after dog dies reveal bridge lever
			if (deadDog && shadow.getOriginX() > 2800)
			{
				bridgeLever.moveUp(1, 550);
			}
			//if dog attacks player then player is dead
			if (shadow.collide(killerDog))
			{
				enterPressed = false;
				gameOver = true;
			}

			//if player is not touching ground then fall
			if (!shadow.collide(ground) && !shadow.collide(ground2) &&
				!shadow.collide(ground3) && !shadow.collide(ground4) &&
				shadow.getOriginY() > 500)
			{
				if (bridgeUp && shadow.getOriginX() < ground2.getOriginX() - ground2.getRadius()
					|| (rockBridge && shadow.getOriginX() > killerRock.getOriginX() - killerRock.getRadius()
					&& shadow.getOriginX() < bridgeOfrocks[2]->getOriginX() + bridgeOfrocks[2]->getRadius()))
				{
					falling = false;
				}
				else
				{
					falling = true;
					shadow.fall(6);
				}
				
			}
			
			//if killer rock hits spike trap
			if (killerRock.collide(spikeTrap))
			{
				rockBridge = true;
			}
			else
			{
				rockBridge = false;
			}
			//if rock bridge has been activated drop rocks from sky
			if (rockBridge && killerRock.getOriginY() >= 600)
			{
				for (int i = 0; i < 3; i++)
				{
					bridgeOfrocks[i]->fallFromSky(600, 12);
				}
				//first save point write to file
				saving.savePoint = 1;
				copyToFile(fileName, saving);
			}
			//if rock not touching ground and trap hasn't been deactivated
			//then rock will fall off ledge
			if (!killerRock.collide(ground) && !killerRock.collide(ground2) &&
				!killerRock.collide(ground3) && !killerRock.collide(bridge) &&
				trapDeactivate && deathTrap1)
			{
				//if rock is not being used as bridge
				if (!rockBridge)
				{
					killerRock.fallFromSky(SCREEN_HEIGHT, 8);
				}
				//else only drop it until ground catches it
				else
				{
					killerRock.fallFromSky(600, 8);
				}
			}
			
			//if rock has fallen off ledge reset because player will need rock
			if (killerRock.getOriginY() > SCREEN_HEIGHT)
			{
				killerRock.resetSetting(950, -100);
				deathTrap1 = false;
				trapDeactivate = false;
			}

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
			//set to true for default
			resumeSelected = true;
			
			//if shadow collides with door and presses action key
			//prompt to enter password
			if (shadow.collide(door) && shadow.action(keyState))
			{
				enterPass = true;
			}
			if (enterPass)
			{
				if (count < 1)
				{
					cout << "Enter password:";
					cin.getline(doorPass, 15);
					
					//check to see if what the user enters is equal
					//to password which is the name they entered
					//when they started the game
					for (int i = 0; doorPass[i] != '\0'; i++)
					{
						if (doorPass[i] != saving.playerName[i])
						{
							correctPass = false;
						}
					}

					//if they are equal 
					if (correctPass)
					{
						cout << "To be continued..." << endl;
					}
					else
					{
						cout << "Come back when you have the answer." << endl;
					}
				}
				count++;
			}
			//if correct password is entered move door up
			if (correctPass && enterPass)
			{
				door.moveUp(3, -700);
				doorUp = true;
			}
			//for now set to game over
			if (door.getOriginY() < -300)
			{
				gameOver = true;
				enterPass = false;
				doorUp = false;
				count = 0;
			}
			//reset if user enters incorrectly so 
			//user can try and enter again
			if (count > 1 && !correctPass)
			{
				count = 0;
				correctPass = true;
				enterPass = false;
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
			startDog = false;
			trapDeactivate = false;
			falling = false;

			//if resume is selected
			if (resumeSelected)
			{
				//draw selected resume button
				selectResume.drawMenu(gameRenderer);
				//draw controls button
				mainMenu.drawMenu(gameRenderer);

				if (gameEvent.type == SDL_KEYDOWN)
				{
					switch (gameEvent.key.keysym.sym)
					{
					//reset values for game
					case SDLK_RETURN:
						if (saving.savePoint < 1)
						{
							cameraX = 0;
							cameraY = 0;
							shadow.resetShadow(gameRenderer, 300, 500);
							killerDog.resetShadow(gameRenderer, 3950, 520);
							killerRock.resetSetting(950, -100);
							bridgeLever.resetSetting(2800, 580);
							rockPosY = 0;
							for (int i = 0; i < 3; i++)
							{
								bridgeOfrocks[i]->resetSettingY(-120 - rockPosY);
								rockPosY += 700;
							}
							enterPressed = true;
							deathTrap1 = false;
							gameOver = false;
							bridgeLocksUp = false;
							deadDog = false;
						}
						if (saving.savePoint >= 1)
						{
							shadow.resetShadow(gameRenderer, 4700, 500);
							//reset camera
							cameraX = -shadow.getOriginX() + SCREEN_WIDTH / 2;
							killerDog.resetShadow(gameRenderer, 3950, 750);
							killerRock.resetSetting(4800, 600);
							bridgeLever.resetSetting(2800, 580);
							rockPosX = 0;
							for (int i = 0; i < 3; i++)
							{
								bridgeOfrocks[i]->resetSetting(4950 + rockPosX, 600);
								rockPosX += 170;
							}
							bridge.resetSetting(2400, 570);
							bridgeLever.resetSettingY(550);
							bridgeUp = true;
							rockBridge = true;
							deathTrap1 = true;
							bridgeLocksUp = true;
							deadDog = true;
							gameOver = false;
							doorUp = false;
							door.resetSettingY(0);
						}
						break;
					case SDLK_DOWN:
						mainMenuSelected = true;
						resumeSelected = false;
						break;
					default:
						break;
					}
				}
			}
			//if controls is selected
			if (mainMenuSelected)
			{
				//draw selected controls button
				selectMainMenu.drawMenu(gameRenderer);
				//draw resume button
				resume.drawMenu(gameRenderer);
				if (gameEvent.type == SDL_KEYDOWN)
				{
					switch (gameEvent.key.keysym.sym)
					{
					case SDLK_RETURN:
						//reset values for game
						cameraX = 0;
						cameraY = 0;
						bridgeLever.resetSetting(2800, 580);
						shadow.resetShadow(gameRenderer, 300, 500);
						killerDog.resetShadow(gameRenderer, 3950, 520);
						killerRock.resetSetting(950, -100);
						rockPosY = 0;
						rockPosY = 0;
						for (int i = 0; i < 3; i++)
						{
							bridgeOfrocks[i]->resetSettingY(-120 - rockPosY);
							rockPosY += 700;
						}
						door.resetSettingY(0);
						deathTrap1 = false;
						gameStart = false;
						mainMenuSelected = false;
						mainMenuScreen = true;
						gameOver = false;
						enterPressed = true;
						bridgeLocksUp = false;
						deadDog = false;
						if (saving.savePoint < 1)
						{
							newGameSelected = true;
						}
						if (saving.savePoint >= 1)
						{
							continueSelected = true;
						}
						break;
					case SDLK_UP:
						resumeSelected = true;
						mainMenuSelected = false;
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
	for (int i = 0; i < 4; i++)
	{
		delete gameBackground[i];
	}
	//deallocate memory
	for (int i = 0; i < 2; i++)
	{
		delete bridgeLock[i];
	}
	//deallocate memory
	for (int i = 0; i < 3; i++)
	{
		delete bridgeOfrocks[i];
	}

	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = NULL;

	SDL_Quit();
	IMG_Quit();

	return 0;
}

//save info to file
void copyToFile(string fileName, SaveInfo saving)
{
	fstream file;
	file.open(fileName.c_str(), ios::out | ios::binary);
	file.write(reinterpret_cast<char *>(&saving), sizeof(saving));
	file.close();
}