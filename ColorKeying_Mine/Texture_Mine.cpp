#include "Texture_Mine.h"

Texture_Mine::Texture_Mine()
{
	//Initialize Variables
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;

	clipRects[0].x = 0;
	clipRects[0].y = 0;
	clipRects[0].w = 100;
	clipRects[0].h = 100;

	clipRects[1].x = 100;
	clipRects[1].y = 0;
	clipRects[1].w = 100;
	clipRects[1].h = 100;

	clipRects[2].x = 0;
	clipRects[2].y = 100;
	clipRects[2].w = 100;
	clipRects[2].h = 100;

	clipRects[3].x = 100;
	clipRects[3].y = 100;
	clipRects[3].w = 100;
	clipRects[3].h = 100;

	animatedRects[0].x = 0;
	animatedRects[0].y = 0;
	animatedRects[0].w = 64;
	animatedRects[0].h = 205;

	animatedRects[1].x = 64;
	animatedRects[1].y = 0;
	animatedRects[1].w = 64;
	animatedRects[1].h = 205;

	animatedRects[2].x = 128;
	animatedRects[2].y = 0;
	animatedRects[2].w = 64;
	animatedRects[2].h = 205;

	animatedRects[3].x = 205;
	animatedRects[3].y = 0;
	animatedRects[3].w = 64;
	animatedRects[3].h = 205;
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
		if (newTexture == NULL)
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

#ifdef SDL_TTF_MAJOR_VERSION
bool Texture_Mine::LoadFromRenderededText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* renderer)
{
	bool success = true;
	Free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Loaded texture
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	if (success)
	{
		mTexture = newTexture;
	}
	return success;


}
#endif

int Texture_Mine::GetHeight()
{
	return mHeight;
}

int Texture_Mine::GetWidth()
{
	return mWidth;
}

void Texture_Mine::Render(int x, int y, SDL_Renderer* gRenderer, bool expandToScreen)
{
	if (mTexture == NULL)
	{
		printf("No texture to render\n");
		return;
	}

	if (expandToScreen)
	{
		SDL_RenderCopy(gRenderer, mTexture, NULL, NULL);
	}
	else 
	{
		//Set rendering space and render to screen
		SDL_Rect renderQuad = { x, y, mWidth, mHeight };
		SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
	}
}

//Method Responsible for clipping an image
void Texture_Mine::Render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
	if (mTexture == NULL)
	{
		printf("No texture to render\n");
		return;
	}

	SDL_Rect renderQuat = { x,y,mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuat.w = clip->w;
		renderQuat.h = clip->h;
	}

	SDL_RenderCopy(renderer, mTexture, clip, &renderQuat);
}

void Texture_Mine::Render(int x, int y, int width, int height, SDL_Renderer* renderer, SDL_Rect* clip)
{
	if (mTexture == NULL)
	{
		printf("No texture to render\n");
		return;
	}
	
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

void Texture_Mine::RenderRotate(int x, int y, float changeTextureSize , SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (mTexture == NULL)
	{
		printf("No texture to render\n");
		return;
	}
	
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w/ changeTextureSize;
		renderQuad.h = clip->h/ changeTextureSize;
	}
	else
	{
		renderQuad.w /= changeTextureSize;
		renderQuad.h /= changeTextureSize;
	}

	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void Texture_Mine::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture_Mine::SetAlpha(Uint8 alpha)
{
	//Modulate Alpha value
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture_Mine::SetBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}