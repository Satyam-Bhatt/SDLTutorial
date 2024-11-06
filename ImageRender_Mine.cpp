#include <stdio.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* image = NULL;


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
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created %s \n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				screenSurface = SDL_GetWindowSurface(window);
				if (screenSurface == NULL)
				{
					printf("Surface could not be created %s \n", SDL_GetError());
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

public:bool LoadMedia()
{
	bool success = true;

	image = LoadSurface("06_extension_libraries_and_loading_other_image_formats/loaded.png");
	if (image == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", "06_extension_libraries_and_loading_other_image_formats/loaded.png", IMG_GetError());
		success = false;
	}

	return success;
}

public:void close()
{
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

				SDL_Rect rect;
				rect.x = value;
				rect.y = 0;
				rect.w = SCREEN_WIDTH / 2;
				rect.h = SCREEN_HEIGHT / 2;
				SDL_BlitScaled(image, NULL, screenSurface, &rect);
				SDL_UpdateWindowSurface(window);
				value += 0.05;
			}
		}
	}

	myClass.close();

	return 0;
}