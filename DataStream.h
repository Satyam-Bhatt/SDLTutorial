
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

#pragma once

class DataStream
{
public:
	//Initializes internals
	DataStream();

	//Loads initial data
	bool loadMedia();

	//Deallocator
	void free();

	//Gets current frame data
	void* getBuffer();

private:
	//Internal Data
	SDL_Surface* images[4];
	int currentImage;
	int delayFrames;
};

