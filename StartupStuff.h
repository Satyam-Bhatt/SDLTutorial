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
#include "Tile.h"
#include <fstream>

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

	//Load Media with Pixel Information and Keying
	bool LoadMedia_TextureManipulation(Texture_Mine& texture, std::string path);

	bool LoadMusic(std::string path, Mix_Music *& music);

	bool LoadSFX(std::string path, Mix_Chunk *& chunk);

	//bool checkCollision(SDL_Rect a, SDL_Rect b);

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

	//Handle window events
	void handleEvent(SDL_Event& e);


	//Window dimensions
	int getWidth();
	int getHeight();

	//Window focus
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	
	// Focuses on window
	void focus();

	// Shows windows contents
	void render();

	bool isShown();

	//Handle Display Switch
	void handleDisplaySwitchAndEvents(SDL_Event & e);

	//Box collision detector
	bool checkCollision_Tiling(SDL_Rect a, SDL_Rect b);

	//Checks collision box against set of tiles
	bool touchesWall(SDL_Rect box, Tile* tiles[]);

	//Sets tiles from tile map
	bool setTiles(Tile * tiles[]);

private:

	//Window Dimesions
	int width;
	int height;
	int windowID;
	int windowDisplayID;

	//Window Focus
	bool mouseFocus;
	bool keyboardFocus;
	bool minimized;
	bool fullscreen;
	bool shown;

	std::vector<SDL_Rect> displayBounds;

};

