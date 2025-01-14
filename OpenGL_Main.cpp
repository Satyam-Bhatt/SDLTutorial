#include "ColorKeying_Mine/Texture_Mine.h"
#include "ColorKeying_Mine/CommonVariables.h"
#include "StartupStuff.h"
#include "MouseEvents_h_cpp/Button.h"
#include "Timer.h"
#include "Dot.h"
#include <fstream>
#include "BitmapFont.h"
#include "DataStream.h"
#include <SDL_thread.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#define SDL_TTF_MAJOR_VERSION

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matricies and clear color
bool initGL();

//Input handler
void handleKeys(unsigned char key, int x, int y);

//Per frame update
void update();

//Renders quad to screen
void render();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQUad = true;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Use Vsync
			if(SDL_GL_SetSwapInterval(1) < 0)
			{
				printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
			}

			//Initialize OpenGL
			if(!initGL())
			{
				printf("Failed to initialize OpenGL!\n");
				success = false;
			}
		}
	}
	return success;
}

int main(int argc, char* args[])
{
	return 0;
}