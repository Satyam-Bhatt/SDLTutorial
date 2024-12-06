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
		window = SDL_CreateWindow("Satayam On Rise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH + 250, SCREEN_HEIGHT + 250, SDL_WINDOW_SHOWN);
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
#endif
