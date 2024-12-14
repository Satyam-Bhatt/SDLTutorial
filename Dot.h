#include <SDL.h>
#include "ColorKeying_Mine/CommonVariables.h"
#include "ColorKeying_Mine/Texture_Mine.h"
#include "StartupStuff.h"
#include <vector>
#include "Circle.h"
#pragma once

class Dot
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	static const int DOT_VEL = 2;

	Dot(int x, int y);

	void handleEvent(SDL_Event& e);
	void move(SDL_Rect& wall);	
	void render(Texture_Mine & detTexture, SDL_Renderer* renderer);

	void renderCicle(Texture_Mine& dotTexture, SDL_Renderer* renderer);

	//MOve Dot and Check collision
	void move(std::vector<SDL_Rect>& otherColliders);

	//Moves the dot and checks collision
	void move(SDL_Rect& square, Circle& circle);

	//Gets the collision boxes
	std::vector<SDL_Rect>& getColliders();

	//Get Collision Circle
	Circle& getColliderCircle();

	// Shows the dot on the screen relative to the camera
	void renderCicleWithCamera(int camX, int camY ,Texture_Mine& dotTexture, SDL_Renderer* renderer);

	//Position Accessors
	int getPosX();
	int getPosY();

private:
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
};

