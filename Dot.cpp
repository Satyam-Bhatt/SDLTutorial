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

	colliderCircle.radius = DOT_WIDTH / 2;

	shiftColliders();
	shiftCircleColliders();

	//Collision box detection
	collider.w = DOT_WIDTH;
	collider.h = DOT_HEIGHT;
}

Dot::~Dot()
{
	//Delete particles
	for(int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		delete particles[i];
	}
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

void Dot::renderCicle(Texture_Mine& dotTexture, SDL_Renderer* renderer)
{
	dotTexture.Render(posX - colliderCircle.radius, posY - colliderCircle.radius, renderer, false);
}

void Dot::renderCicleWithCamera(int camX, int camY, Texture_Mine& dotTexture, SDL_Renderer* renderer)
{
	int xRelative = posX - camX;
	int yRelative = posY - camY;

	dotTexture.Render(xRelative - colliderCircle.radius, yRelative - colliderCircle.radius, renderer, false);
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

void Dot::move(SDL_Rect& square, Circle& circle)
{
	posX += velX;
	shiftCircleColliders();

	//If the dot collided or went too far to the left or right
	if ((posX - colliderCircle.radius < 0) || (posX + colliderCircle.radius > SCREEN_WIDTH_CAMERA) || startup-> checkCollision(colliderCircle, square) || startup->checkCollision(colliderCircle, circle))
	{
		//Move back
		posX -= velX;
		shiftCircleColliders();
	}

	//Move the dot up or down
	posY += velY;
	shiftCircleColliders();

	//If the dot collided or went too far up or down
	if ((posY - colliderCircle.radius < 0) || (posY + colliderCircle.radius > SCREEN_HEIGHT_CAMERA) || startup->checkCollision(colliderCircle, square) || startup->checkCollision(colliderCircle, circle))
	{
		//Move back
		posY -= velY;
		shiftCircleColliders();
	}
}

void Dot::move(Tile* tiles[])
{
	box.x += velX;

	//if the dot went too far to the left or right
	if ((box.x < 0) || (box.x + DOT_WIDTH > SCREEN_WIDTH_CAMERA) || startup->touchesWall(box, tiles))
	{
		box.x -= velX;
	}

	//Move the dot up or down
	box.y += velY;

	//if the dot went too far up or down
	if ((box.y < 0) || (box.y + DOT_HEIGHT > SCREEN_HEIGHT_CAMERA) || startup->touchesWall(box, tiles))
	{
		box.y -= velY;
	}
}

std::vector<SDL_Rect>& Dot::getColliders()
{
	return colliders;
}

Circle& Dot::getColliderCircle()
{
	return colliderCircle;
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

void Dot::shiftCircleColliders()
{
	//Align collider to center of dot
	colliderCircle.x = posX;
	colliderCircle.y = posY;
}

void Dot::renderWithCamera(SDL_Rect& camera, Texture_Mine& texture, SDL_Renderer* renderer)
{
	texture.Render(box.x - camera.x, box.y - camera.y, renderer, false);
}

int Dot::getPosX()
{
	return posX;
}

int Dot::getPosY()
{
	return posY;
}

void Dot::renderParticles_Mine(Texture_Mine *& t, Texture_Mine& s)
{
	//Initialize particles
	for(int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		particles[i] = new Particle(posX , posY , t, s);
	}
}

void Dot::renderParticles(int camX, int camY, Texture_Mine *& t, Texture_Mine& s, SDL_Renderer* renderer)
{
	//Go through particles
	for(int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		//Delete and replace particle
		if (particles[i]->isDead())
		{
			delete particles[i];
			particles[i] = new Particle(posX - camX, posY - camY, t, s);
		}
	}

	//Show particles
	for(int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		particles[i]->render(renderer);
	}
}

void Dot::setCamera(SDL_Rect& camera)
{
	//Center the camera over the dot
	camera.x = (box.x + DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (box.y + DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}

	if (camera.y < 0)
	{
		camera.y = 0;
	}

	if (camera.x > SCREEN_WIDTH_CAMERA - camera.w)
	{
		camera.x = SCREEN_WIDTH_CAMERA - camera.w;
	}

	if (camera.y > SCREEN_HEIGHT_CAMERA - camera.h)
	{
		camera.y = SCREEN_HEIGHT_CAMERA - camera.h;
	}
}




