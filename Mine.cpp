#include <SDL.h>
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
//Image
SDL_Surface* image = NULL;

class MineFirstClass {
	//Screen Dimensions
	const int S_Widht = 800;
	const int S_Height = 600;

//public:bool init_Mine();
//public:bool loadMedia_Mine();
//public:void close_Mine();
	  //Initialzie
public:bool init_MIne()
{
	bool success = false;
	if (SDL_Init((SDL_INIT_VIDEO)) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		window = SDL_CreateWindow("Rendering Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_Widht, S_Height, SDL_WINDOW_MAXIMIZED);
		if (window == NULL)
		{
			printf("Window could not come thright %s", SDL_GetError());
			return false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			//SDL_UpdateWindowSurface(window);
			success = true;
		}
	}
	return success;
}

public:bool loadMedia_Mine()
{
	bool success = true;

	image = SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");
	if (image == NULL)
	{
		printf("error %s", SDL_GetError());
		success = false;
	}

	return success;
}

public:void close_Mine()
{
	SDL_FreeSurface(image);
	image = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}
};


int main( int argc, char* args[] )
{
	MineFirstClass firstClass;

	if( !firstClass.init_MIne() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !firstClass.loadMedia_Mine() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Event handler
			SDL_Event e;

			bool quit = false;

			//Apply the image
			SDL_BlitSurface( image, NULL, screenSurface, NULL );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );

            //Hack to get window to stay up
            //SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
			
			//Application is running
			while (!quit)
			{
			    int a=SDL_PollEvent(&e);
				
				while (a != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if(e.type == SDL_KEYDOWN)
					{
							printf("key\n");
					}
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						printf("mouse\n");
					}
					//if (e.type == SDL_MOUSEMOTION) {
					//	//printf("mouse motion\n");
					//}

					printf("%d\n", a);
					a = SDL_PollEvent(&e);
					printf("Sister Nonsense: %d\n", a);

				}
			}
		}
	}

	//Free resources and close SDL
	firstClass.close_Mine();

	return 0;
}
