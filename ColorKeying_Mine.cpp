// This code does 
// - Color keying - removes a color from the image
// - Loading Textures in style Proper Method

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include "ColorKeying_Mine/Texture_Mine.h"

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

int main(int argc, char* args[])
{
	Texture_Mine texture;
	printf("Hello, World! %d \n" , texture.GetHeight());
	return 0;
}