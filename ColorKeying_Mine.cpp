// This code does 
// - Color keying - removes a color from the image
// - Loading Textures in style Proper Method
// - Sprite Sheet and Clipping

#include "ColorKeying_Mine/Texture_Mine.h"
#include "ColorKeying_Mine/CommonVariables.h"
#include "StartupStuff.h"

StartupStuff* startupStuff = new StartupStuff();
Texture_Mine texture_1, texture_2, texture_3;

void close()
{
	texture_1.Free();
	texture_2.Free();
	texture_3.Free();

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
		if(!startupStuff->LoadMedia(texture_1, "10_color_keying/foo.png") || !startupStuff->LoadMedia(texture_2, "10_color_keying/background.png") || !startupStuff->LoadMedia(texture_3, "11_clip_rendering_and_sprite_sheets/dots.png"))
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

				texture_2.Render(0, 0, startupStuff->renderer, false);
				texture_1.Render(420, 200, startupStuff->renderer, false);

				texture_3.Render(SCREEN_WIDTH / 2 - texture_3.GetWidth() / 2, SCREEN_HEIGHT / 2 - texture_3.GetHeight() / 2, startupStuff->renderer, false);
				
				texture_3.Render(0, 0, startupStuff->renderer, &texture_3.clipRects[0]);
				texture_3.Render(SCREEN_WIDTH - texture_3.clipRects[1].w, 0, startupStuff->renderer, &texture_3.clipRects[1]);
				texture_3.Render(0, SCREEN_HEIGHT - texture_3.clipRects[2].h, startupStuff->renderer, &texture_3.clipRects[2]);
				texture_3.Render(SCREEN_WIDTH - texture_3.clipRects[3].w, SCREEN_HEIGHT - texture_3.clipRects[3].h, startupStuff->renderer, &texture_3.clipRects[3]);

				SDL_RenderPresent(startupStuff->renderer);
			}
		}
	}
	close();
	startupStuff->Free();
	return 0;
}