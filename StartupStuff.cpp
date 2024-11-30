#include "StartupStuff.h"
#include "ColorKeying_Mine/CommonVariables.h"

StartupStuff::StartupStuff()
{
	window = NULL;
	renderer = NULL;
}

StartupStuff::~StartupStuff()
{
	Free();
}

void StartupStuff::Free()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
}

bool StartupStuff::init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow("Satayam On Rise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if(TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool StartupStuff::LoadMedia(Texture_Mine& texture, std::string path)
{
	bool success = true;
	if(!texture.LoadFromFile(path, renderer))
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	return success;
}

bool StartupStuff::LoadMedia(Texture_Mine& texture, std::string path, SDL_BlendMode blendMode)
{
	bool success = true;
	if(!texture.LoadFromFile(path, renderer))
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	else
	{
		texture.SetBlendMode(blendMode);
	}
	return success;
}

#ifdef SDL_TTF_MAJOR_VERSION
bool StartupStuff::LoadText(TTF_Font* gFont, std::string fontPath, std::string textureText, SDL_Color textColor, int fontSize, Texture_Mine& texture)
{
	bool success = true;

	gFont = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		if (!texture.LoadFromRenderededText(textureText, textColor, gFont, renderer))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}
	return success;
}
#endif
