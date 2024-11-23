// This code does 
// - Color keying - removes a color from the image
// - Loading Textures in style Proper Method

#include "ColorKeying_Mine/Texture_Mine.h"
#include "ColorKeying_Mine/CommonVariables.h"
#include "StartupStuff.h"

StartupStuff* startupStuff = new StartupStuff();
Texture_Mine texture_1, texture_2;

void close()
{
	texture_1.Free();
	texture_2.Free();

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!startupStuff->init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if(!startupStuff->LoadMedia(texture_1, "10_color_keying/foo.png") || !startupStuff->LoadMedia(texture_2, "10_color_keying/background.png"))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0) 
				{
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				SDL_SetRenderDrawColor(startupStuff->renderer, 255, 255, 255, 255);
				SDL_RenderClear(startupStuff->renderer);

				texture_2.Render(0, 0, startupStuff->renderer);
				texture_1.Render(320, 200, startupStuff->renderer);

				SDL_RenderPresent(startupStuff->renderer);
			}
		}
	}
	close();
	startupStuff->Free();
	return 0;
}