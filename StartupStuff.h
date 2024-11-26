#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "ColorKeying_Mine/Texture_Mine.h"

class StartupStuff
{
public: 
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	StartupStuff();
	~StartupStuff();
	void Free();
	bool init();
	bool LoadMedia(Texture_Mine& texture, std::string path);

	//Load Media with Blend Mode
	bool LoadMedia(Texture_Mine& texture, std::string path, SDL_BlendMode blending);
};

