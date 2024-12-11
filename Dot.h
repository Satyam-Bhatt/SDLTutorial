#include <SDL.h>
#include "ColorKeying_Mine/CommonVariables.h"
#include "ColorKeying_Mine/Texture_Mine.h"
#include "StartupStuff.h"
#include <vector>
#pragma once

class Dot
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	static const int DOT_VEL = 1;

	Dot(int x, int y);

	void handleEvent(SDL_Event& e);
	void move(SDL_Rect& wall);	
	void render(Texture_Mine & detTexture, SDL_Renderer* renderer);

	//MOve Dot and Check collision
	void move(std::vector<SDL_Rect>& otherColliders);

	//Gets the collision boxes
	std::vector<SDL_Rect>& getColliders();

private:
	int posX, posY;

	int velX, velY;

	SDL_Rect collider;

	StartupStuff* startup;

	//Dot's collision boxes
	std::vector<SDL_Rect> colliders;

	//Moves the collision boxes relative to the dot's offset
	void shiftColliders();
};

