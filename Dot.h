#include <SDL.h>
#include "ColorKeying_Mine/CommonVariables.h"
#include "ColorKeying_Mine/Texture_Mine.h"
#pragma once

class Dot
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	static const int DOT_VEL = 10;

	Dot();

	void handleEvent(SDL_Event& e);
	void move();	
	void render(Texture_Mine & detTexture, SDL_Renderer* renderer);

private:
	int posX, posY;

	int velX, velY;
};

