#include "StartupStuff.h"
#include "ColorKeying_Mine/CommonVariables.h"

StartupStuff::StartupStuff()
{
	window = NULL;
	renderer = NULL;
}

StartupStuff::~StartupStuff()
{
	Free();
}

void StartupStuff::Free()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	if (joyHaptic != NULL) SDL_HapticClose(joyHaptic);

	if (joyStick != NULL) SDL_JoystickClose(joyStick);

	if (gameController != NULL) SDL_GameControllerClose(gameController);

	gameController = NULL;
	joyHaptic = NULL;
	joyStick = NULL;
	window = NULL;
	renderer = NULL;
}

bool StartupStuff::init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Check for joysticks
		if (SDL_NumJoysticks() < 1)
		{
			printf("Warning: No joysticks connected!\n");
		}
		else
		{
			//Check if the first controller is game controller interface
			if (!SDL_IsGameController(0))
			{
				printf("Warning: Joystick is not game controller interface compatible! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Open game controller
				gameController = SDL_GameControllerOpen(0);
				if (gameController == NULL)
				{
					printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
				}
			}

			//Load joystick if game controller is NULL
			if (gameController == NULL)
			{
				joyStick = SDL_JoystickOpen(0);
				if (joyStick == NULL)
				{
					printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
				}
				else
				{
					//Check if Joystick supports haptics
					if (!SDL_JoystickIsHaptic(joyStick))
					{
						printf("Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError());
					}
					else
					{
						//Get joystick haptic device
						joyHaptic = SDL_HapticOpenFromJoystick(joyStick);
						if (joyHaptic == NULL)
						{
							printf("Warning: Unable to get joystick haptics! SDL Error: %s\n", SDL_GetError());
						}
						else
						{
							//Initialize joystick haptics
							if (SDL_HapticRumbleInit(joyHaptic) < 0)
							{
								printf("Warning: Unable to initialize joystick haptics! SDL Error: %s\n", SDL_GetError());
							}
						}
					}
				}
			}
		}

		//Create window
		window = SDL_CreateWindow("Satayam On Rise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH + SCREEN_EXTENTION, SCREEN_HEIGHT + SCREEN_EXTENTION, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				//Initialize Image loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error %s\n", TTF_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool StartupStuff::LoadMedia(Texture_Mine& texture, std::string path)
{
	bool success = true;
	if (!texture.LoadFromFile(path, renderer))
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}

bool StartupStuff::LoadMedia(Texture_Mine& texture, std::string path, SDL_BlendMode blendMode)
{
	bool success = true;
	if (!texture.LoadFromFile(path, renderer))
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	else
	{
		texture.SetBlendMode(blendMode);
	}
	return success;
}

bool StartupStuff::LoadMusic(std::string path, Mix_Music*& music)
{
	bool success = true;

	music = Mix_LoadMUS(path.c_str());
	if (music == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

bool StartupStuff::LoadSFX(std::string path, Mix_Chunk*& chunk)
{
	bool success = true;

	chunk = Mix_LoadWAV(path.c_str());
	if (chunk == NULL)
	{
		printf("Failed to load SFX! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

bool StartupStuff::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA = a.x;
	int rightA = a.x + a.w;
	int topA = a.y;
	int bottomA = a.y + a.h;

	int leftB = b.x;
	int rightB = b.x + b.w;
	int topB = b.y;
	int bottomB = b.y + b.h;

	if(bottomA <= topB)
	{
		return false;
	}

	if(topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

bool StartupStuff::checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
	//Sided of rectangle
	int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;

	//Go through the A rectangle
	for (int i = 0; i < a.size(); i++)
	{
		leftA = a[i].x;
		rightA = a[i].x + a[i].w;
		topA = a[i].y;
		bottomA = a[i].y + a[i].h;

		for (int j = 0; j < b.size(); j++)
		{
			leftB = b[j].x;
			rightB = b[j].x + b[j].w;
			topB = b[j].y;
			bottomB = b[j].y + b[j].h;

			//If no sides from A are outside of B
			if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
			{
				//Collision Detected
				return true;
			}
		}
	}

	//If the boxes don't touch
	return false;
}

bool StartupStuff::checkCollision(Circle& a, Circle& b)
{
	//Total Radius Squared
	int totalRadiusSquared = a.radius + b.radius;
	totalRadiusSquared *= totalRadiusSquared;

	//If distance between the center of the circle is less than the sum of their radii
	if (distanceSquared(a.x, a.y, b.x, b.y) < totalRadiusSquared)
	{
		//Circle collided
		return true;
	}

	return false;
}

bool StartupStuff::checkCollision(Circle& a, SDL_Rect& b)
{
	//Closest point on collision box
	int cX, cY;

	//Find closest x offset
	if (a.x < b.x)
	{
		cX = b.x;
	}
	else if (a.x > b.x + b.w)
	{
		cX = b.x + b.w;
	}
	else
	{
		cX = a.x;
	}

	//Find closest y offset
	if (a.y < b.y)
	{
		cY = b.y;
	}
	else if (a.y > b.y + b.h)
	{
		cY = b.y + b.h;
	}
	else
	{
		cY = a.y;
	}

	//If the closest point is inside the circle
	if (distanceSquared(a.x, a.y, cX, cY) < a.radius * a.radius)
	{
		//This box and the circle have collided
		return true;
	}

	return false;
}

double StartupStuff::distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}


#ifdef SDL_TTF_MAJOR_VERSION
bool StartupStuff::LoadText(TTF_Font * & gFont, std::string fontPath, std::string textureText, SDL_Color textColor, int fontSize, Texture_Mine& texture)
{
	bool success = true;

	gFont = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		if (!texture.LoadFromRenderededText(textureText, textColor, gFont, renderer))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}
bool StartupStuff::LoadText_Save(TTF_Font*& gFont, std::string fontPath, std::string textureText, SDL_Color textColor, int fontSize, Texture_Mine* texture, 
	Sint32 data[TOTAL_DATA])
{
	bool success = true;

	//Open file for reading in binary
	SDL_RWops* file = SDL_RWFromFile("33_file_reading_and_writing/nums.bin", "r+b");
	//File does not exist
	if (file == NULL)
	{
		printf("Warning: Unable to open file!SDL Error : % s\n", SDL_GetError());

		//Create file for writing
		file = SDL_RWFromFile("33_file_reading_and_writing/nums.bin", "w+b");

		if (file != NULL)
		{
			printf("New file created!\n");

			//Initialize Data
			for (size_t i = 0; i < TOTAL_DATA; i++)
			{
				data[i] = 0;
				SDL_RWwrite(file, &data[i], sizeof(Sint32), 1);
			}

			//Close file handler
			SDL_RWclose(file);
		}
		else
		{
			printf("Error: Unable to create file! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
	}
	//File Exists
	else
	{
		//Load Data
		printf("Reading file...!\n");
		for(int i = 0; i < TOTAL_DATA; i++)
		{
			SDL_RWread(file, &data[i], sizeof(Sint32), 1);
		}
		//Close file handler
		SDL_RWclose(file);
	}

	SDL_Color textColor_ = { 0, 0, 0, 0xFF };
	SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };

	//Initialize data textures
	texture[0].LoadFromRenderededText(std::to_string(data[0]), highlightColor, gFont, renderer);
	for (int i = 1; i < TOTAL_DATA; ++i)
	{
		texture[i].LoadFromRenderededText(std::to_string(data[i]), textColor_, gFont, renderer);
	}

	return success;
}

#endif
