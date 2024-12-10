#include "Dot.h"

Dot::Dot()
{
	posX = 0;
	posY = 0;

	velX = 0;
	velY = 0;

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


