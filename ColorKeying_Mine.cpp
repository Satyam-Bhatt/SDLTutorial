// This code does 
// - Color keying - removes a color from the image
// - Loading Textures in style Proper Method
// - Sprite Sheet and Clipping
// - Color Modulation
// - Rotation of sprite
// - Animated Sprites
// - Alpha Blending
// - Text Rendering
// - Mouse Events

#include "ColorKeying_Mine/Texture_Mine.h"
#include "ColorKeying_Mine/CommonVariables.h"
#include "StartupStuff.h"
#include "MouseEvents_h_cpp/Button.h"
#define SDL_TTF_MAJOR_VERSION

StartupStuff* startupStuff = new StartupStuff();

TTF_Font* gFont = NULL;

Texture_Mine texture_1, texture_2, texture_3, texture_4, texture_5, texture_animated, texture_rotated, texture_text;

Texture_Mine buttonSprite;
Button button[TOTAL_BUTTONS];

void close()
{
	texture_1.Free();
	texture_2.Free();
	texture_3.Free();
	texture_4.Free();
	texture_5.Free();
	texture_animated.Free();
	texture_rotated.Free();
	texture_text.Free();
	buttonSprite.Free();

	TTF_CloseFont(gFont);
	gFont = NULL;

	startupStuff->Free();
	delete startupStuff;
	startupStuff = nullptr;

	TTF_Quit();
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
		if (!startupStuff->LoadMedia(texture_1, "10_color_keying/foo.png")
			|| !startupStuff->LoadMedia(texture_2, "10_color_keying/background.png")
			|| !startupStuff->LoadMedia(texture_3, "11_clip_rendering_and_sprite_sheets/dots.png")
			|| !startupStuff->LoadMedia(texture_4, "12_color_modulation/colors.png")
			|| !startupStuff->LoadMedia(texture_5, "13_alpha_blending/fadeout.png", SDL_BLENDMODE_BLEND)
			|| !startupStuff->LoadMedia(texture_animated, "14_animated_sprites_and_vsync/foo.png")
			|| !startupStuff->LoadMedia(texture_rotated, "15_rotation_and_flipping/arrow.png")
			|| !startupStuff->LoadMedia(buttonSprite, "17_mouse_events/button.png"))
		{
			printf("Failed to load media!\n");
		}
		else
		{
#ifdef SDL_TTF_MAJOR_VERSION 
			if (!startupStuff->LoadText(gFont, "16_true_type_fonts/lazy.ttf", "Hello World", { 0, 0, 0 }, 60, texture_text))
			{
				printf("Failed to render text texture!\n");
			}
#endif

			bool quit = false;
			SDL_Event e;

			Uint8 r = 255;
			Uint8 g = 255;
			Uint8 b = 255;
			Uint8 a = 255;

			int frame = 0;

			double degrees = 0;

			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			button[0].SetPosition(0, 120);
			button[1].SetPosition(SCREEN_WIDTH - BUTTON_WIDTH/4, 120);
			button[2].SetPosition(120, SCREEN_HEIGHT - BUTTON_HEIGHT/4 - 50);
			button[3].SetPosition(SCREEN_WIDTH - BUTTON_WIDTH/4 - 120, SCREEN_HEIGHT - BUTTON_HEIGHT/4 - 50);

			while (!quit)
			{
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

								//Increase degrees
							case SDLK_l:
								degrees += 10;
								break;

								//Decrease degrees
							case SDLK_k:
								degrees -= 10;
								break;
						}
					}

					for (int i = 0; i < TOTAL_BUTTONS; ++i)
					{
						button[i].HandleEvent(&e);
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

				texture_animated.Render(100, 120, startupStuff->renderer, &texture_animated.animatedRects[frame / 16]);

				texture_rotated.RenderRotate(500, 250, 3, startupStuff->renderer, NULL, degrees, NULL, flipType);

#ifdef  SDL_TTF_MAJOR_VERSION
				
				texture_text.Render(150, 150, startupStuff->renderer, false);

#endif
				for(int i = 0; i < TOTAL_BUTTONS; i++)
				{
					button[i].Render(&buttonSprite ,startupStuff->renderer);
				}

				SDL_RenderPresent(startupStuff->renderer);


				frame++;
				if (frame / 16 > 3)
				{
					frame = 0;
				}
			}
		}
	}
	close();
	return 0;
}