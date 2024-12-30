#pragma once
#include <string>
#include "ColorKeying_Mine/Texture_Mine.h"

class BitmapFont
{
public:
	//Constructor
	BitmapFont();

	//Generates the font
	bool buildFont(std::string fontFile, SDL_Renderer* renderer);

	//Deallocates font
	void free();

	//Shows the text
	void renderText(int x, int y, std::string text);

private:
	//The font texture
	Texture_Mine fontTexture;

	//Individual character in the surface
	SDL_Rect chars[256];

	//Spacing Variable
	int newLine, space;
};

