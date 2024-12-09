#include "Dot.h"

Dot::Dot()
{
	posX = 0;
	posY = 0;

	velX = 0;
	velY = 0;
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

void Dot::move()
{
	posX += velX;

	//If the dot went too far right or left
	if((posX < 0 ) || (posX + DOT_WIDTH > SCREEN_WIDTH))
	{
		posX -= velX;
	}

	posY += velY;

	if ((posY < 0) || (posY + DOT_HEIGHT > SCREEN_HEIGHT))
	{
		posY -= velY;
	}
}

void Dot::render(Texture_Mine& texture, SDL_Renderer* renderer)
{
	texture.Render(posX, posY, renderer, false);
}


