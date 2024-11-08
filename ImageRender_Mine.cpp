#include <stdio.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* image = NULL;
SDL_Texture* imageTexture = NULL;


class MyClass {

public: bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not be initialized %s \n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled! \n");
		}

		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created %s \n", SDL_GetError());
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created %s \n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

public:SDL_Surface* LoadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

public:SDL_Texture* LoadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

public:bool LoadMedia()
{
	bool success = true;

	imageTexture = LoadTexture("06_extension_libraries_and_loading_other_image_formats/loaded.png");
	if (imageTexture == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", "06_extension_libraries_and_loading_other_image_formats/loaded.png", IMG_GetError());
		success = false;
	}

	return success;
}

public:void close()
{
	SDL_DestroyTexture(imageTexture);
	imageTexture = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_FreeSurface(image);
	image = NULL;

	SDL_FreeSurface(screenSurface);
	screenSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

};

float value = 0;

int main(int argc, char* args[])
{
	MyClass myClass;

	if (!myClass.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!myClass.LoadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				if (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				SDL_SetRenderDrawColor(renderer, 0xFF, 60, 0xFF, 0xFF);

				//Clear Screen
				SDL_RenderClear(renderer);

				SDL_Rect rect;
				rect.x = value;
				rect.y = sin(rect.x / 2) * 40;
				rect.w = SCREEN_WIDTH / 2;
				rect.h = SCREEN_HEIGHT / 2;

				//Render Texture to Screen
				SDL_RenderCopy(renderer, imageTexture, NULL, &rect);
				//IMG_LoadTexture(renderer, "06_extension_libraries_and_loading_other_image_formats/loaded.png"); //Not working


				SDL_Rect rectFilled;
				rectFilled.x = SCREEN_WIDTH / 4;
				rectFilled.y = SCREEN_HEIGHT / 4;
				rectFilled.w = SCREEN_WIDTH / 2;
				rectFilled.h = SCREEN_HEIGHT / 2;
				//Can also be defined as -> SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
				SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderFillRect(renderer, &rectFilled);

				SDL_Rect rectLine;
				rectLine.x = SCREEN_WIDTH / 6;
				rectLine.y = SCREEN_HEIGHT / 6;
				rectLine.w = SCREEN_WIDTH * 2 / 3;
				rectLine.h = SCREEN_HEIGHT * 2 / 3;
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
				SDL_RenderDrawRect(renderer, &rectLine);

				SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
				SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
				for (int i = SCREEN_HEIGHT / 4; i < SCREEN_HEIGHT / 2; i+= 4)
				{
					SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i);
				}

				//Update Screen
				SDL_RenderPresent(renderer);

				value += 0.005;
			}
		}
	}

	myClass.close();

	return 0;
}