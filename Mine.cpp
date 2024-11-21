//Responsible for Taking inputs and changinf images

//#include <SDL.h>
//#include <stdio.h>
//#include <string>
//
//SDL_Window* window = NULL;
//SDL_Surface* screenSurface = NULL;
////Image
//SDL_Surface* image = NULL;
//
//enum KeyPressSurfaces
//{
//	KEY_PRESS_SURFACE_DEFAULT,
//	KEY_PRESS_SURFACE_UP,
//	KEY_PRESS_SURFACE_DOWN,
//	KEY_PRESS_SURFACE_LEFT,
//	KEY_PRESS_SURFACE_RIGHT,
//	KEY_PRESS_SURFACE_TOTAL
//};
//
//SDL_Surface* allImagesLoaded[KEY_PRESS_SURFACE_TOTAL];
//
//SDL_Surface* loadSurface(std::string path)
//{
//	SDL_Surface* optimizedSurface = NULL;
//	SDL_Surface* temporarySurface = SDL_LoadBMP(path.c_str());
//	if (temporarySurface == NULL)
//	{
//		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//	}
//	else
//	{
//		optimizedSurface = SDL_ConvertSurface(temporarySurface, screenSurface->format, 0);
//		if (optimizedSurface == NULL)
//		{
//			printf("OptimizedSurfaceIssue %s \n", SDL_GetError());
//		}
//
//		//Free the loaded Surface
//		SDL_FreeSurface(temporarySurface);
//	}
//
//	return optimizedSurface;
//}
//
//class MineFirstClass {
//	//Screen Dimensions
//	public:const int S_Widht = 800;
//	public:const int S_Height = 600;
//
//	//Initialzie
//	public:bool init_MIne()
//	{
//		bool success = false;
//		if (SDL_Init((SDL_INIT_VIDEO)) < 0)
//		{
//			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//			return false;
//		}
//		else
//		{
//			window = SDL_CreateWindow("Rendering Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_Widht, S_Height, SDL_WINDOW_MAXIMIZED);
//			if (window == NULL)
//			{
//				printf("Window could not come thright %s", SDL_GetError());
//				return false;
//			}
//			else
//			{
//				screenSurface = SDL_GetWindowSurface(window);
//				//SDL_UpdateWindowSurface(window);
//				success = true;
//			}
//		}
//		return success;
//	}
//
//	public:bool loadMedia_Mine()
//	{
//		bool success = true;
//
//		allImagesLoaded[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("04_key_presses/press.bmp");
//		if (allImagesLoaded[KEY_PRESS_SURFACE_DEFAULT] == NULL)
//		{
//			printf("Unable to load default image! SDL Error: %s\n", SDL_GetError());
//			success = false;
//		}
//
//		allImagesLoaded[KEY_PRESS_SURFACE_UP] = loadSurface("04_key_presses/up.bmp");
//		if (allImagesLoaded[KEY_PRESS_SURFACE_UP] == NULL)
//		{
//			printf("Unable to load up image! SDL Error: %s\n", SDL_GetError());
//			success = false;
//		}
//
//		allImagesLoaded[KEY_PRESS_SURFACE_DOWN] = loadSurface("04_key_presses/down.bmp");
//		if (allImagesLoaded[KEY_PRESS_SURFACE_DOWN] == NULL)
//		{
//			printf("Unable to load down image! SDL Error: %s\n", SDL_GetError());
//			success = false;
//		}
//
//		allImagesLoaded[KEY_PRESS_SURFACE_LEFT] = loadSurface("04_key_presses/left.bmp");
//		if (allImagesLoaded[KEY_PRESS_SURFACE_LEFT] == NULL)
//		{
//			printf("Unable to load left image! SDL Error: %s\n", SDL_GetError());
//			success = false;
//		}
//
//		allImagesLoaded[KEY_PRESS_SURFACE_RIGHT] = loadSurface("04_key_presses/right.bmp");
//		if (allImagesLoaded[KEY_PRESS_SURFACE_RIGHT] == NULL)
//		{
//			printf("Unable to load right image! SDL Error: %s\n", SDL_GetError());
//			success = false;
//		}
//
//		return success;
//	}
//
//	public:void close_Mine()
//	{
//		for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
//		{
//			SDL_FreeSurface(allImagesLoaded[i]);
//			allImagesLoaded[i] = NULL;
//		}
//
//		SDL_FreeSurface(image);
//		image = NULL;
//		SDL_DestroyWindow(window);
//		window = NULL;
//		SDL_Quit();
//	}
//};
//
//int main(int argc, char* args[])
//{
//	MineFirstClass firstClass;
//
//	if (!firstClass.init_MIne())
//	{
//		printf("Failed to initialize!\n");
//	}
//	else
//	{
//		if (!firstClass.loadMedia_Mine())
//		{
//			printf("Failed to load media!\n");
//		}
//		else
//		{
//			//Event handler
//			SDL_Event e;
//
//			bool quit = false;
//
//			image = allImagesLoaded[KEY_PRESS_SURFACE_DEFAULT];
//
//			//Hack to get window to stay up
//			//SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
//
//			//Application is running
//			while (!quit)
//			{
//				while (SDL_PollEvent(&e) != 0)
//				{
//					if (e.type == SDL_QUIT)
//					{
//						quit = true;
//					}
//					//if (e.key.keysym.sym == SDLK_UP)
//					//{
//					//	image = allImagesLoaded[KEY_PRESS_SURFACE_UP];
//					//}
//
//					switch (e.key.keysym.sym) 
//					{
//						case SDLK_UP:
//							image = allImagesLoaded[KEY_PRESS_SURFACE_UP];
//							break;
//						case SDLK_DOWN:
//							image = allImagesLoaded[KEY_PRESS_SURFACE_DOWN];
//							break;
//						case SDLK_LEFT:
//							image = allImagesLoaded[KEY_PRESS_SURFACE_LEFT];
//							break;
//						case SDLK_RIGHT:
//							image = allImagesLoaded[KEY_PRESS_SURFACE_RIGHT];
//							break;
//						default:
//							image = allImagesLoaded[KEY_PRESS_SURFACE_DEFAULT];
//							break;
//					}
//
//					//Apply the image
//					//SDL_BlitSurface(image, NULL, screenSurface, NULL);
//					SDL_Rect rect;
//					rect.x = 0;
//					rect.y = 0;
//					rect.w = firstClass.S_Widht;
//					rect.h = firstClass.S_Height;
//					SDL_BlitScaled(image, NULL, screenSurface, &rect);
//
//					//Update the surface
//					SDL_UpdateWindowSurface(window);
//
//					//if (e.type == SDL_MOUSEMOTION) {
//					//	//printf("mouse motion\n");
//					//}
//				}
//			}
//		}
//	}
//
//	//Free resources and close SDL
//	firstClass.close_Mine();
//
//	return 0;
//}
