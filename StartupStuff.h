#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include "ColorKeying_Mine/Texture_Mine.h"

class StartupStuff
{
public: 
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	//Game controller handler with force feedback
	SDL_GameController* gameController = NULL;

	//Joystick handles with Haptics
	SDL_Joystick* joyStick = NULL;
	SDL_Haptic* joyHaptic = NULL;


	StartupStuff();
	~StartupStuff();
	void Free();
	bool init();
	bool LoadMedia(Texture_Mine& texture, std::string path);

	//Load Media with Blend Mode
	bool LoadMedia(Texture_Mine& texture, std::string path, SDL_BlendMode blending);

#ifdef SDL_TTF_MAJOR_VERSION
	//Load Text
	bool LoadText(TTF_Font* gFont, std::string fontPath, std::string textureText, SDL_Color textColor, int fontSize, Texture_Mine& texture);
#endif

private:


};

