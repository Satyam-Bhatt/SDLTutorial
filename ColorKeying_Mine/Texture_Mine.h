#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>

class Texture_Mine
{
public:
	//Initialize Variables
	Texture_Mine();

	//Deallocate memory
	~Texture_Mine();

	//Loads image at specified path
	bool LoadFromFile(std::string path, SDL_Renderer* renderer);

#ifdef SDL_TTF_MAJOR_VERSION
	//Creates image from Text 
	bool LoadFromRenderededText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer); 
#endif

	//Deallocates texture
	void Free();

	//Set color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set Alpha modulation
	void SetAlpha(Uint8 alpha);

	//Set Blend Mode
	void SetBlendMode(SDL_BlendMode blending);

	//Renders texture at given point
	void Render(int x, int y, SDL_Renderer* renderer, bool expandToScreen = false);

	//Method Responsible for clipping an image and also rendering it at a given point
	void Render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL);

	//Method to render and rotate the texture
	void RenderRotate(int x, int y, float changeTextureSize = 1 , SDL_Renderer* renderer = NULL, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Method to render texture for a given height and width
	void Render(int x, int y, int width, int height, SDL_Renderer* renderer);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

	SDL_Rect clipRects[4];
	SDL_Rect animatedRects[4];

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	//Image dimensions
	int mWidth;
	int mHeight;
};