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

void tileClipsInit()
{
	tileClips[TILE_RED].x = 0;
	tileClips[TILE_RED].y = 0;
	tileClips[TILE_RED].w = TILE_WIDTH;
	tileClips[TILE_RED].h = TILE_HEIGHT;

	tileClips[TILE_GREEN].x = 0;
	tileClips[TILE_GREEN].y = 80;
	tileClips[TILE_GREEN].w = TILE_WIDTH;
	tileClips[TILE_GREEN].h = TILE_HEIGHT;

	tileClips[TILE_BLUE].x = 0;
	tileClips[TILE_BLUE].y = 160;
	tileClips[TILE_BLUE].w = TILE_WIDTH;
	tileClips[TILE_BLUE].h = TILE_HEIGHT;

	tileClips[TILE_TOPLEFT].x = 80;
	tileClips[TILE_TOPLEFT].y = 0;
	tileClips[TILE_TOPLEFT].w = TILE_WIDTH;
	tileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

	tileClips[TILE_LEFT].x = 80;
	tileClips[TILE_LEFT].y = 80;
	tileClips[TILE_LEFT].w = TILE_WIDTH;
	tileClips[TILE_LEFT].h = TILE_HEIGHT;

	tileClips[TILE_BOTTOMLEFT].x = 80;
	tileClips[TILE_BOTTOMLEFT].y = 160;
	tileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
	tileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

	tileClips[TILE_TOP].x = 160;
	tileClips[TILE_TOP].y = 0;
	tileClips[TILE_TOP].w = TILE_WIDTH;
	tileClips[TILE_TOP].h = TILE_HEIGHT;

	tileClips[TILE_CENTER].x = 160;
	tileClips[TILE_CENTER].y = 80;
	tileClips[TILE_CENTER].w = TILE_WIDTH;
	tileClips[TILE_CENTER].h = TILE_HEIGHT;

	tileClips[TILE_BOTTOM].x = 160;
	tileClips[TILE_BOTTOM].y = 160;
	tileClips[TILE_BOTTOM].w = TILE_WIDTH;
	tileClips[TILE_BOTTOM].h = TILE_HEIGHT;

	tileClips[TILE_TOPRIGHT].x = 240;
	tileClips[TILE_TOPRIGHT].y = 0;
	tileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
	tileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

	tileClips[TILE_RIGHT].x = 240;
	tileClips[TILE_RIGHT].y = 80;
	tileClips[TILE_RIGHT].w = TILE_WIDTH;
	tileClips[TILE_RIGHT].h = TILE_HEIGHT;

	tileClips[TILE_BOTTOMRIGHT].x = 240;
	tileClips[TILE_BOTTOMRIGHT].y = 160;
	tileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
	tileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
}

//bool setTiles(Tile* tiles[])
//{
//	//Success flag
//	bool tilesLoaded = true;
//
//	//The tile offsets
//	int x = 0, y = 0;
//
//	//Open the map
//	std::ifstream map("39_tiling/lazy.map");
//
//	//If the map couldn't be loaded
//	if (map.fail())
//	{
//		printf("Unable to load map file!\n");
//		tilesLoaded = false;
//	}
//	else
//	{
//		//Initialize the tiles
//		for (int i = 0; i < TOTAL_TILES; ++i)
//		{
//			//Determines what kind of tile will be made
//			int tileType = -1;
//
//			//Read tile from map file
//			map >> tileType;
//
//			//If the was a problem in reading the map
//			if (map.fail())
//			{
//				//Stop loading map
//				printf("Error loading map: Unexpected end of file!\n");
//				tilesLoaded = false;
//				break;
//			}
//
//			//If the number is a valid tile number
//			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
//			{
//				tiles[i] = new Tile(x, y, tileType);
//			}
//			//If we don't recognize the tile type
//			else
//			{
//				//Stop loading map
//				printf("Error loading map: Invalid tile type at %d!\n", i);
//				tilesLoaded = false;
//				break;
//			}
//
//			//Move to next tile spot
//			x += TILE_WIDTH;
//
//			//If we've gone too far
//			if (x >= SCREEN_WIDTH_CAMERA)
//			{
//				//Move back
//				x = 0;
//
//				//Move to the next row
//				y += TILE_HEIGHT;
//			}
//		}
//
//		//Clip the sprite sheet
//		if (tilesLoaded)
//		{
//			tileClips[TILE_RED].x = 0;
//			tileClips[TILE_RED].y = 0;
//			tileClips[TILE_RED].w = TILE_WIDTH;
//			tileClips[TILE_RED].h = TILE_HEIGHT;
//
//			tileClips[TILE_GREEN].x = 0;
//			tileClips[TILE_GREEN].y = 80;
//			tileClips[TILE_GREEN].w = TILE_WIDTH;
//			tileClips[TILE_GREEN].h = TILE_HEIGHT;
//
//			tileClips[TILE_BLUE].x = 0;
//			tileClips[TILE_BLUE].y = 160;
//			tileClips[TILE_BLUE].w = TILE_WIDTH;
//			tileClips[TILE_BLUE].h = TILE_HEIGHT;
//
//			tileClips[TILE_TOPLEFT].x = 80;
//			tileClips[TILE_TOPLEFT].y = 0;
//			tileClips[TILE_TOPLEFT].w = TILE_WIDTH;
//			tileClips[TILE_TOPLEFT].h = TILE_HEIGHT;
//
//			tileClips[TILE_LEFT].x = 80;
//			tileClips[TILE_LEFT].y = 80;
//			tileClips[TILE_LEFT].w = TILE_WIDTH;
//			tileClips[TILE_LEFT].h = TILE_HEIGHT;
//
//			tileClips[TILE_BOTTOMLEFT].x = 80;
//			tileClips[TILE_BOTTOMLEFT].y = 160;
//			tileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
//			tileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;
//
//			tileClips[TILE_TOP].x = 160;
//			tileClips[TILE_TOP].y = 0;
//			tileClips[TILE_TOP].w = TILE_WIDTH;
//			tileClips[TILE_TOP].h = TILE_HEIGHT;
//
//			tileClips[TILE_CENTER].x = 160;
//			tileClips[TILE_CENTER].y = 80;
//			tileClips[TILE_CENTER].w = TILE_WIDTH;
//			tileClips[TILE_CENTER].h = TILE_HEIGHT;
//
//			tileClips[TILE_BOTTOM].x = 160;
//			tileClips[TILE_BOTTOM].y = 160;
//			tileClips[TILE_BOTTOM].w = TILE_WIDTH;
//			tileClips[TILE_BOTTOM].h = TILE_HEIGHT;
//
//			tileClips[TILE_TOPRIGHT].x = 240;
//			tileClips[TILE_TOPRIGHT].y = 0;
//			tileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
//			tileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;
//
//			tileClips[TILE_RIGHT].x = 240;
//			tileClips[TILE_RIGHT].y = 80;
//			tileClips[TILE_RIGHT].w = TILE_WIDTH;
//			tileClips[TILE_RIGHT].h = TILE_HEIGHT;
//
//			tileClips[TILE_BOTTOMRIGHT].x = 240;
//			tileClips[TILE_BOTTOMRIGHT].y = 160;
//			tileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
//			tileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
//		}
//	}
//
//	//Close the file
//	map.close();
//
//	//If the map was loaded fine
//	return tilesLoaded;
//}

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
			Tile* tiles[TOTAL_TILES];

			if( !startupStuff->setTiles( tiles))
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

			tileClipsInit();

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
				//camera.x = dot.getPosX() - (SCREEN_WIDTH + SCREEN_EXTENTION) / 2;
				//camera.y = dot.getPosY() - (SCREEN_HEIGHT + SCREEN_EXTENTION) / 2;

				////Keep Camera in bounds
				//if (camera.x < 0)
				//{
				//	camera.x = 0;
				//}
				//if (camera.y < 0)
				//{
				//	camera.y = 0;
				//}
				//if (camera.x > SCREEN_WIDTH_CAMERA - camera.w)
				//{
				//	camera.x = SCREEN_WIDTH_CAMERA - camera.w;
				//}
				//if (camera.y > SCREEN_HEIGHT_CAMERA - camera.h)
				//{
				//	camera.y = SCREEN_HEIGHT_CAMERA - camera.h;
				//}

				if (tiles[0] == NULL)
				{
					printf("Tile 0 is NULL\n");
				}

				//dot.move_Tiling(tiles);
				//dot.setCamera(camera);

				//Only draw if window is not minimized
				if (!startupStuff->isMinimized())
				{
					SDL_SetRenderDrawColor(startupStuff->renderer, 255, 255, 0, 255);
					SDL_RenderClear(startupStuff->renderer);

					//dot.renderCicleWithCamera(camera.x, camera.y, dotTexture, startupStuff->renderer);
					for(int i = 0; i < TOTAL_TILES; i++)
					{
						if (tiles[i] == NULL)
						{
							printf("Tile %d is NULL\n", i);
						}
						//else
						//	tiles[i]->render(camera, tileTexture, startupStuff->renderer, tileClips[tiles[i]->getType()]);
					}

					dot.renderParticles(camera.x, camera.y, pointerToColorTextures, shimmerTexture, startupStuff->renderer);

				   // dot.renderWithCamera(camera, dotTexture, startupStuff->renderer);


					SDL_RenderPresent(startupStuff->renderer);
				}
			}
		}
	}

	close();
	return 0;
}