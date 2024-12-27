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
			Tile * tiles[TOTAL_TILES];

			if( !startupStuff->setTiles( tiles ) )
			{
				printf( "Failed to load tile set!\n" );
			}


			bool quit = false;
			SDL_Event e;;

			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			//Moving Dot
			Dot dot(20, 20);

			//Dot To Collide With
			Dot collideDot(100, 100);

			//The camera area
			SDL_Rect camera = { 0,0, SCREEN_WIDTH + SCREEN_EXTENTION, SCREEN_HEIGHT + SCREEN_EXTENTION };

			//particle
			colorTexture[0].SetAlpha(192);
			colorTexture[1].SetAlpha(192);
			colorTexture[2].SetAlpha(192);
			shimmerTexture.SetAlpha(192);

			Texture_Mine* pointerToColorTextures = colorTexture;

			dot.renderParticles_Mine(pointerToColorTextures, shimmerTexture);

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

					dot.handleEvent(e);
				}

				//------ For Rect Collision Detection ------------
				//dot.move(wall);
				//--------------------

				//------ For Per Pixel Collision Detection ------ 
				/* std::vector<SDL_Rect> multipleCollider = collideDot.getColliders();
				multipleCollider.push_back(wall);
				dot.move(multipleCollider); */
				//---------------------

				//--------------- For Circle and Rect Collistion Detection ----------------
				//dot.move(falkeWall, collideDot.getColliderCircle());
				//-----------------------

				//-------- CAMERA ----------
				camera.x = dot.getPosX() - (SCREEN_WIDTH + SCREEN_EXTENTION) / 2;
				camera.y = dot.getPosY() - (SCREEN_HEIGHT + SCREEN_EXTENTION) / 2;

				//Keep Camera in bounds
				if (camera.x < 0)
				{
					camera.x = 0;
				}
				if (camera.y < 0)
				{
					camera.y = 0;
				}
				if (camera.x > SCREEN_WIDTH_CAMERA - camera.w)
				{
					camera.x = SCREEN_WIDTH_CAMERA - camera.w;
				}
				if (camera.y > SCREEN_HEIGHT_CAMERA - camera.h)
				{
					camera.y = SCREEN_HEIGHT_CAMERA - camera.h;
				}

				//Only draw if window is not minimized
				if (!startupStuff->isMinimized())
				{
					SDL_SetRenderDrawColor(startupStuff->renderer, 255, 255, 0, 255);
					SDL_RenderClear(startupStuff->renderer);

					dot.renderCicleWithCamera(camera.x, camera.y, dotTexture, startupStuff->renderer);


					dot.renderParticles(camera.x, camera.y, pointerToColorTextures, shimmerTexture, startupStuff->renderer);

					SDL_RenderPresent(startupStuff->renderer);
				}
			}
		}
	}

	close();
	return 0;
}