#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Texture_Mine
{
public:
	//Initialize Variables
	Texture_Mine();

	//Deallocate memory
	~Texture_Mine();

	//Loads image at specified path
	bool LoadFromFile(std::string path, SDL_Renderer* renderer);

	//Deallocates texture
	void Free();

	//Renders texture at given point
	void Render(int x, int y, SDL_Renderer* renderer, bool expandToScreen = false);

	void Render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

	SDL_Rect clipRects[4];

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	//Image dimensions
	int mWidth;
	int mHeight;
};