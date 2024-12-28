#include "Tile.h"

Tile::Tile(int x, int y, int tileType)
{
	//Get the offset
	box.x = x;
	box.y = y;

	//Set the collision box
	box.w = TILE_WIDTH;
	box.h = TILE_HEIGHT;

	//Get the tile type
	type = tileType;
}

void Tile::render(SDL_Rect& camera, Texture_Mine& tileTexture, SDL_Renderer* renderer, SDL_Rect clip)
{
	//If the tile is on screen
	//if (startupStuff->checkCollision(camera, box))
	//{
		tileTexture.Render(box.x - camera.x, box.y - camera.y, renderer, &clip);
	//}
}

int Tile::getType()
{
	return type;
}

SDL_Rect Tile::getBox()
{
	return box;
}
