// This code does 
// - Tiling of a level

#include "ColorKeying_Mine/Texture_Mine.h"
#include "ColorKeying_Mine/CommonVariables.h"
#include "StartupStuff.h"
#include "MouseEvents_h_cpp/Button.h"
#include "Timer.h"
#include "Dot.h"
#include <fstream>
#define SDL_TTF_MAJOR_VERSION

StartupStuff* startupStuff = new StartupStuff();

TTF_Font* gFont = NULL, * gFont2 = NULL;

Texture_Mine dotTexture, tileTexture;

SDL_Rect tileClips[TOTAL_TILE_SPRITES];

//Particle Textures
Texture_Mine colorTexture[3];
Texture_Mine shimmerTexture;

void close()
{
	dotTexture.Free();
	shimmerTexture.Free();
	for (int i = 0; i < 3; i++)
	{
		colorTexture[i].Free();
	}

	TTF_CloseFont(gFont);
	gFont = NULL;
	TTF_CloseFont(gFont2);
	gFont2 = NULL;

	startupStuff->Free();
	delete startupStuff;
	startupStuff = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

int main(int argc, char* args[])
{
	if (!startupStuff->init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!startupStuff->LoadMedia(dotTexture, "39_tiling/dot.bmp")
			|| !startupStuff->LoadMedia(colorTexture[0], "38_particle_engines/red.bmp")
			|| !startupStuff->LoadMedia(colorTexture[1], "38_particle_engines/green.bmp")
			|| !startupStuff->LoadMedia(colorTexture[2], "38_particle_engines/blue.bmp")
			|| !startupStuff->LoadMedia(shimmerTexture, "38_particle_engines/shimmer.bmp")
			|| !startupStuff->LoadMedia(tileTexture, "39_tiling/tiles.png"))
		{
			printf("Failed to load media!\n");
		}
		else
		{
#ifdef SDL_TTF_MAJOR_VERSION 
			//if (!startupStuff->LoadText(gFont, "16_true_type_fonts/lazy.ttf", "Hello World", { 0, 0, 0 }, 60, texture_text))
			//{
			//	printf("Failed to render text texture!\n");
			//}
#endif

			bool quit = false;
			SDL_Event e;;


			while (!quit)
			{
				bool renderText = false;

				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Key press events
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{

						}
					}

				}

				//Only draw if window is not minimized
				if (!startupStuff->isMinimized())
				{
					SDL_SetRenderDrawColor(startupStuff->renderer, 255, 255, 0, 255);
					SDL_RenderClear(startupStuff->renderer);

					SDL_RenderPresent(startupStuff->renderer);
				}
			}
		}
	}

	close();
	return 0;
}