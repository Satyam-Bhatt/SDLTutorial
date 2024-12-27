#pragma once
#include <SDL.h>
#include "ColorKeying_Mine/CommonVariables.h"
#include "ColorKeying_Mine/Texture_Mine.h"
#include "StartupStuff.h"

class Tile
{
public:
	//Initialize position and type
	Tile(int x, int y, int tileType);

	//Show the tile
	void render(SDL_Rect& camera, Texture_Mine& tileTexture, SDL_Renderer* renderer, SDL_Rect clip);

	//Get the collision box
	SDL_Rect getBox();

	//Get the tile type
	int getType();

private:
	//The attribute of the tile
	SDL_Rect box;

	StartupStuff* startupStuff;

	//The tile type
	int type;
};

