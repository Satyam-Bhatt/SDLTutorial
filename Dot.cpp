#include "Dot.h"

Dot::Dot(int x, int y)
{
	posX = x;
	posY = y;

	velX = 0;
	velY = 0;

	colliders.resize(11);

	//Initialize the collision boxes' width and height
	colliders[0].w = 6;
	colliders[0].h = 1;

	colliders[1].w = 10;
	colliders[1].h = 1;

	colliders[2].w = 14;
	colliders[2].h = 1;

	colliders[3].w = 16;
	colliders[3].h = 2;

	colliders[4].w = 18;
	colliders[4].h = 2;

	colliders[5].w = 20;
	colliders[5].h = 6;

	colliders[6].w = 18;
	colliders[6].h = 2;

	colliders[7].w = 16;
	colliders[7].h = 2;

	colliders[8].w = 14;
	colliders[8].h = 1;

	colliders[9].w = 10;
	colliders[9].h = 1;

	colliders[10].w = 6;
	colliders[10].h = 1;

	shiftColliders();

	//Collision box detection
	collider.w = DOT_WIDTH;
	collider.h = DOT_HEIGHT;
}

void Dot::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			velY = -DOT_VEL;
			break;
		case SDLK_DOWN:
			velY = DOT_VEL;
			break;
		case SDLK_LEFT:
			velX = -DOT_VEL;
			break;
		case SDLK_RIGHT:
			velX = DOT_VEL;
			break;
		}
	}

	if(e.type == SDL_KEYUP)
	{
		switch(e.key.keysym.sym)
		{
		case SDLK_UP:
			velY = 0;
			break;
		case SDLK_DOWN:
			velY = 0;
			break;
		case SDLK_LEFT:
			velX = 0;
			break;
		case SDLK_RIGHT:
			velX = 0;
			break;
		}
	}
}

void Dot::move(SDL_Rect& wall)
{
	posX += velX;
	collider.x = posX;

	//If the dot went too far right or left
	if((posX < 0 ) || (posX + DOT_WIDTH > SCREEN_WIDTH + SCREEN_EXTENTION) || startup->checkCollision(collider, wall))
	{
		posX -= velX;
		collider.x = posX;
	}

	posY += velY;
	collider.y = posY;

	if ((posY < 0) || (posY + DOT_HEIGHT > SCREEN_HEIGHT + SCREEN_EXTENTION) || startup->checkCollision(collider, wall))
	{
		posY -= velY;
		collider.y = posY;
	}
}

void Dot::render(Texture_Mine& texture, SDL_Renderer* renderer)
{
	texture.Render(posX, posY, renderer, false);
}

void Dot::move(std::vector<SDL_Rect>& otherColliders)
{
	posX += velX;
	shiftColliders();

	if ((posX < 0) || (posX + DOT_WIDTH > SCREEN_WIDTH + SCREEN_EXTENTION) || startup->checkCollision(colliders, otherColliders))
	{
		posX -= velX;
		shiftColliders();
	}

	posY += velY;
	shiftColliders();

	if ((posY < 0) || (posY + DOT_HEIGHT > SCREEN_HEIGHT + SCREEN_EXTENTION) || startup->checkCollision(colliders, otherColliders))
	{
		posY -= velY;
		shiftColliders();
	}
}

std::vector<SDL_Rect>& Dot::getColliders()
{
	return colliders;
}

void Dot::shiftColliders()
{
	//Row offset
	int r = 0;

	//Go through the dots collision boxes
	for (int set = 0; set < colliders.size(); ++set)
	{
		//Center the collision box
		colliders[set].x = posX + (DOT_WIDTH - colliders[set].w) / 2;

		//Set the collision box at its row offset
		colliders[set].y = posY + r;

		//Move the row offset down the height of the collision box
		r += colliders[set].h;
	}
}




