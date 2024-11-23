#include "Texture_Mine.h"

Texture_Mine::Texture_Mine()
{
	//Initialize Variables
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture_Mine::~Texture_Mine()
{
	Free();
}

void Texture_Mine::Free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

//Loads up mTexture from a file
bool Texture_Mine::LoadFromFile(std::string path, SDL_Renderer* renderer)
{
	bool success = true;

	//Get rid of preexisting texture
	Free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Loaded texture
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		success = false;
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			success = false;
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	
	if (success)
	{
		mTexture = newTexture;
	}
	return success;
}

int Texture_Mine::GetHeight()
{
	return mHeight;
}

int Texture_Mine::GetWidth()
{
	return mWidth;
}

void Texture_Mine::Render(int x, int y, SDL_Renderer* gRenderer)
{
	if (mTexture == NULL)
	{
		//printf("No texture to render\n");
		return;
	}

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}