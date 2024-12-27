#pragma once
#include "ColorKeying_Mine/Texture_Mine.h"
#include "SDL_render.h"

class Particle
{
public:
	//Initialize position and animation
	Particle(int x, int y, Texture_Mine *& t, Texture_Mine& s);

	//Shows the particle
	void render(SDL_Renderer* renderer);

	//Checks if particle is dead
	bool isDead();

private:
	//Offsets
	int posX, posY;

	//Current frame of animation
	int frame;

	//Type of particle
	Texture_Mine * particleTexture;

	//Shimmer
	Texture_Mine shimmerTexture;
};

