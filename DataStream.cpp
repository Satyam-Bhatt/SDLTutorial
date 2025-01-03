#include "DataStream.h"

DataStream::DataStream()
{
	images[0] = NULL;
	images[1] = NULL;
	images[2] = NULL;
	images[3] = NULL;

	currentImage = 0;
	delayFrames = 20;
}

bool DataStream::loadMedia()
{
	bool success = true;

	for (int i = 0; i < 4; ++i)
	{
		std::stringstream path;
		path << "42_texture_streaming/foo_walk_" << i << ".png";

		SDL_Surface* loadedSurface = IMG_Load(path.str().c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load %s! SDL_image error: %s\n", path.str().c_str(), IMG_GetError());
			success = false;
		}
		else
		{
			images[i] = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
		}

		SDL_FreeSurface(loadedSurface);
	}

	return success;
}

void DataStream::free()
{
	for (int i = 0; i < 4; ++i)
	{
		SDL_FreeSurface(images[i]);
		images[i] = NULL;
	}
}

void* DataStream::getBuffer()
{
	--delayFrames;
	if (delayFrames == 0)
	{
		++currentImage;
		delayFrames = 20;
	}

	if (currentImage == 4)
	{
		currentImage = 0;
	}

	return images[currentImage]->pixels;
}
