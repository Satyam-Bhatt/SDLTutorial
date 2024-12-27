#include "Particle.h"

Particle::Particle(int x, int y, Texture_Mine *& t, Texture_Mine& s)
{
	//Set offsets
	posX = x - 5 + (rand() % 25);
	posY = y - 5 + (rand() % 25);

	//Initialize animation
	frame = rand() % 5;

	//Set Type
	switch (rand() % 3)
	{
		case 0: particleTexture = &t[0]; break;
		case 1: particleTexture = &t[1]; break;
		case 2: particleTexture = &t[2]; break;
	}

	shimmerTexture = s;
}

void Particle::render(SDL_Renderer* renderer)
{
	//Show image
	particleTexture->Render(posX, posY, renderer, false );

	//Show shimmer
	if (frame % 2 == 0)
	{
		shimmerTexture.Render(posX, posY, renderer, false );
	}

	//Animate
	frame++;
}

bool Particle::isDead()
{
	return frame >= 10;
}
