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

Texture_Mine bitMapRender, streamingTexture;

BitmapFont texture_text;

DataStream dataStream;

void close()
{
	dataStream.free();
	texture_text.free();

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
			|| !dataStream.loadMedia())
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

					bitMapRender.Render((SCREEN_WIDTH - bitMapRender.GetWidth()) / 2, (SCREEN_HEIGHT - bitMapRender.GetHeight()) / 2,
						startupStuff->renderer, false);

					texture_text.renderText(0,0, "AAAaaaaBBBbbbcasomdwew\nasdawd\nnn  asdasd \nsjkdn", startupStuff->renderer);

					streamingTexture.lockTexture();
					streamingTexture.copyRawPixels32(dataStream.getBuffer());
					streamingTexture.unlockTexture();

					streamingTexture.Render(0, 0, startupStuff->renderer, false);

					SDL_RenderPresent(startupStuff->renderer);
				}
			}
		}
	}

	close();
	return 0;
}