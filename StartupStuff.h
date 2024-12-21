#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <sstream>
#include "ColorKeying_Mine/Texture_Mine.h"
#include "vector"
#include "Circle.h"
#include "ColorKeying_Mine/CommonVariables.h"

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

	bool LoadMusic(std::string path, Mix_Music *& music);

	bool LoadSFX(std::string path, Mix_Chunk *& chunk);

	bool checkCollision(SDL_Rect a, SDL_Rect b);

	bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

	//Circle/Circle collision detector
	bool checkCollision(Circle& a, Circle& b);

	//Circle/Box collision detector
	bool checkCollision(Circle& a, SDL_Rect& b);

	//Calculates distance squared between two points
	double distanceSquared(int x1, int y1, int x2, int y2);

#ifdef SDL_TTF_MAJOR_VERSION
	//Load Text
	bool LoadText(TTF_Font * & gFont, std::string fontPath, std::string textureText, SDL_Color textColor, int fontSize, Texture_Mine& texture);

	//Load and save
	bool LoadText_Save(TTF_Font*& gFont, std::string fontPath, std::string textureText, SDL_Color textColor, int fontSize, Texture_Mine* texture, Sint32 data[TOTAL_DATA]);

	//LOad Audio
	bool LoadAudio(TTF_Font*& gFont, SDL_Color textColor, Texture_Mine* texture, int& recordingDeviceCount);

	//Load Text and Audio

#endif

	//Creates renderer from internal window
	SDL_Renderer* createRenderer();

	//Handle window events
	void handleEvent(SDL_Event& e);

	//Window dimensions
	int getWidth();
	int getHeight();

	//Window focus
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();

private:

	//Window Dimesions
	int width;
	int height;

	//Window Focus
	bool mouseFocus;
	bool keyboardFocus;
	bool minimized;
	bool fullscreen;

};

