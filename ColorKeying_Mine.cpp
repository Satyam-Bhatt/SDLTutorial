// This code does 
// - Color keying - removes a color from the image
// - Loading Textures in style Proper Method
// - Sprite Sheet and Clipping
// - Color Modulation

#include "ColorKeying_Mine/Texture_Mine.h"
#include "ColorKeying_Mine/CommonVariables.h"
#include "StartupStuff.h"

StartupStuff* startupStuff = new StartupStuff();
Texture_Mine texture_1, texture_2, texture_3, texture_4, texture_5;

void close()
{
	texture_1.Free();
	texture_2.Free();
	texture_3.Free();
	texture_4.Free();
	delete startupStuff;
	startupStuff = nullptr;

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
		if(!startupStuff->LoadMedia(texture_1, "10_color_keying/foo.png")
			|| !startupStuff->LoadMedia(texture_2, "10_color_keying/background.png") 
			|| !startupStuff->LoadMedia(texture_3, "11_clip_rendering_and_sprite_sheets/dots.png") 
			|| !startupStuff->LoadMedia(texture_4, "12_color_modulation/colors.png")
			|| !startupStuff->LoadMedia(texture_5, "13_alpha_blending/fadeout.png", SDL_BLENDMODE_BLEND))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			Uint8 r = 255;
			Uint8 g = 255;
			Uint8 b = 255;
			Uint8 a = 255;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0) 
				{
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
					//Key press events
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
							//Increase red
							case SDLK_r:
							r += 32;
							break;
							
							//Increase green
							case SDLK_g:
							g += 32;
							break;
							
							//Increase blue
							case SDLK_b:
							b += 32;
							break;

							//Decrease red
							case SDLK_e:
							r -= 32;
							break;
							
							//Decrease green
							case SDLK_f:
							g -= 32;
							break;
							
							//Decrease blue
							case SDLK_v:
							b -= 32;
							break;

							//Decrease alpha
							case SDLK_s:
							a -= 32;
							break;

							//Increase alpha
							case SDLK_a:
							a += 32;
							break;
						}
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

				texture_4.SetColor(r, g, b);
				texture_4.Render(SCREEN_WIDTH / 2 - 50, 0, 100, 100, startupStuff->renderer);

				texture_5.SetAlpha(a);
				texture_5.Render(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 100, 120, 100, startupStuff->renderer);


				SDL_RenderPresent(startupStuff->renderer);
			}
		}
	}
	close();
	startupStuff->Free();
	return 0;
}