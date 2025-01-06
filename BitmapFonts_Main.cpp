// This code does 
// - Tiling of a level

#include "ColorKeying_Mine/Texture_Mine.h"
#include "ColorKeying_Mine/CommonVariables.h"
#include "StartupStuff.h"
#include "MouseEvents_h_cpp/Button.h"
#include "Timer.h"
#include "Dot.h"
#include <fstream>
#include "BitmapFont.h"
#include "DataStream.h"
#define SDL_TTF_MAJOR_VERSION

StartupStuff* startupStuff = new StartupStuff();

TTF_Font* gFont = NULL, * gFont2 = NULL;

Texture_Mine bitMapRender, streamingTexture, targetTexture;

BitmapFont texture_text;

DataStream dataStream;

void close()
{
	dataStream.free();
	texture_text.free();
	targetTexture.Free();

	bitMapRender.Free();

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
		if (!startupStuff->LoadMedia_TextureManipulation(bitMapRender, "40_texture_manipulation/foo.png")
			|| !texture_text.buildFont("41_bitmap_fonts/lazyfont.png", startupStuff->renderer, startupStuff->window)
			|| !streamingTexture.createBlank(64, 205, startupStuff->renderer)
			|| !dataStream.loadMedia()
			|| !targetTexture.createBlank(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_TEXTUREACCESS_TARGET ,startupStuff->renderer))
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

			double angle = 0;
			SDL_Point screenCenter = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
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

				angle += 2;
				if (angle > 360)
				{
					angle -= 360;
				}

				//Set self as render target
				targetTexture.SetAsRenderTarget(startupStuff->renderer);

				//Only draw if window is not minimized
				//if (!startupStuff->isMinimized())
				//{
					SDL_SetRenderDrawColor(startupStuff->renderer, 255, 255, 0, 255);
					SDL_RenderClear(startupStuff->renderer);

					//bitMapRender.Render((SCREEN_WIDTH - bitMapRender.GetWidth()) / 2, (SCREEN_HEIGHT - bitMapRender.GetHeight()) / 2,
					//	startupStuff->renderer, false);

					//texture_text.renderText(0,0, "AAAaaaaBBBbbbcasomdwew\nasdawd\nnn  asdasd \nsjkdn", startupStuff->renderer);

					//streamingTexture.lockTexture();
					//streamingTexture.copyRawPixels32(dataStream.getBuffer());
					//streamingTexture.unlockTexture();

					//streamingTexture.Render(0, 0, startupStuff->renderer, false);

					//Render red filled quad
					SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
					SDL_SetRenderDrawColor(startupStuff->renderer, 0xFF, 0x00, 0x00, 0xFF);
					SDL_RenderFillRect(startupStuff->renderer, &fillRect);

					//Render green outlined quad
					SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
					SDL_SetRenderDrawColor(startupStuff->renderer, 0x00, 0xFF, 0x00, 0xFF);
					SDL_RenderDrawRect(startupStuff->renderer, &outlineRect);

					//Draw blue horizontal line
					SDL_SetRenderDrawColor(startupStuff->renderer, 0x00, 0x00, 0xFF, 0xFF);
					SDL_RenderDrawLine(startupStuff->renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

					//Draw vertical line of yellow dots
					SDL_SetRenderDrawColor(startupStuff->renderer, 0xFF, 0xFF, 0x00, 0xFF);
					for (int i = 0; i < SCREEN_HEIGHT; i += 4)
					{
						SDL_RenderDrawPoint(startupStuff->renderer, SCREEN_WIDTH / 2, i);
					}

					//Reset Render target
					SDL_SetRenderTarget(startupStuff->renderer, NULL);

					//Show rendered to texture
					//targetTexture.Render(0, 0, startupStuff->renderer, false);
					targetTexture.RenderRotate(0, 0, 1, startupStuff->renderer, NULL, angle, &screenCenter);

					SDL_RenderPresent(startupStuff->renderer);
				//}
			}
		}
	}

	close();
	return 0;
}