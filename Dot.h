#include <SDL.h>
#include "ColorKeying_Mine/CommonVariables.h"
#include "ColorKeying_Mine/Texture_Mine.h"
#include "StartupStuff.h"
#include <vector>
#include "Circle.h"
#include "Particle.h"
#include "ColorKeying_Mine/CommonVariables.h"
#include "Tile.h"
#pragma once

class Dot
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	static const int DOT_VEL = 2;

	Dot(int x, int y);

	~Dot();

	void handleEvent(SDL_Event& e);
	void move(SDL_Rect& wall);	
	void render(Texture_Mine & detTexture, SDL_Renderer* renderer);

	void renderCicle(Texture_Mine& dotTexture, SDL_Renderer* renderer);

	//MOve Dot and Check collision
	void move(std::vector<SDL_Rect>& otherColliders);

	//Moves the dot and checks collision
	void move(SDL_Rect& square, Circle& circle);

	//Moves the dot and check collision against the tiles
	void move_Tiling(Tile* tiles[]);

	//Gets the collision boxes
	std::vector<SDL_Rect>& getColliders();

	//Get Collision Circle
	Circle& getColliderCircle();

	// Shows the dot on the screen relative to the camera
	void renderCicleWithCamera(int camX, int camY ,Texture_Mine& dotTexture, SDL_Renderer* renderer);

	//Render Particles
	void renderParticles_Mine(Texture_Mine *& t, Texture_Mine & s);

	//Show the particles
	void renderParticles(int camX, int camY, Texture_Mine *& t, Texture_Mine& s, SDL_Renderer* renderer);

	//Centers the camera over the dot
	void setCamera(SDL_Rect& camera);

	//Shows the dot on the screen relative to the camera
	void renderWithCamera(SDL_Rect& camera, Texture_Mine& texture, SDL_Renderer* renderer);

	//Position Accessors
	int getPosX();
	int getPosY();

private:
	//The particles
	Particle* particles[TOTAL_PARTICLES];

	int posX, posY;

	int velX, velY;

	SDL_Rect collider;

	StartupStuff* startup;

	//Dot's collision boxes
	std::vector<SDL_Rect> colliders;
	
	//Dots collision circle
	Circle colliderCircle;

	//Moves the collision boxes relative to the dot's offset
	void shiftColliders();

	void shiftCircleColliders();

	//Collision box of the dot
	SDL_Rect box;
};

