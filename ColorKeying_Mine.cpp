// This code does 
// - Color keying - removes a color from the image
// - Loading Textures in style Proper Method
// - Sprite Sheet and Clipping
// - Color Modulation
// - Rotation of sprite
// - Animated Sprites
// - Alpha Blending
// - Text Rendering
// - Mouse Events
// - Key States
// - Joystick Input
// - Controller Rumble
// - Timer
// - Start Stop Timer
// - Average FPS
// - Motion

#include "ColorKeying_Mine/Texture_Mine.h"
#include "ColorKeying_Mine/CommonVariables.h"
#include "StartupStuff.h"
#include "MouseEvents_h_cpp/Button.h"
#include "Timer.h"
#include "Dot.h"
#define SDL_TTF_MAJOR_VERSION

StartupStuff* startupStuff = new StartupStuff();

TTF_Font* gFont = NULL, * gFont2 = NULL;

Texture_Mine texture_1, texture_2, texture_3, texture_4, texture_5, texture_animated, texture_rotated, texture_text, joystick_Texture, audio_Texture, prompt_Texture, timeTextTexture, start_PromptTexture, pause_PromptTexture, timerTextTexture2;

Texture_Mine fpsTimer_Texture, dotTexture, collidePrompt_Texture;

Texture_Mine buttonSprite;
Button button[TOTAL_BUTTONS];

//Key State Textures
Texture_Mine pressTexture, upTexture, downTexture, leftTexture, rightTexture;

//Music
Mix_Music* music = NULL;

//Sound Effects
Mix_Chunk* scratch = NULL, * high = NULL, * medium = NULL, * low = NULL;

void close()
{
	texture_1.Free();
	texture_2.Free();
	texture_3.Free();
	texture_4.Free();
	texture_5.Free();
	texture_animated.Free();
	texture_rotated.Free();
	texture_text.Free();
	buttonSprite.Free();
	pressTexture.Free();
	upTexture.Free();
	downTexture.Free();
	leftTexture.Free();
	rightTexture.Free();
	joystick_Texture.Free();
	audio_Texture.Free();
	prompt_Texture.Free();
	timeTextTexture.Free();
	start_PromptTexture.Free();
	pause_PromptTexture.Free();
	timerTextTexture2.Free();
	fpsTimer_Texture.Free();
	dotTexture.Free();
	collidePrompt_Texture.Free();

	//Free Sound Effects
	Mix_FreeChunk(scratch);
	Mix_FreeChunk(high);
	Mix_FreeChunk(medium);
	Mix_FreeChunk(low);
	scratch = NULL;
	high = NULL;
	medium = NULL;
	low = NULL;

	//Free Music
	Mix_FreeMusic(music);
	music = NULL;

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
		if (!startupStuff->LoadMedia(texture_1, "10_color_keying/foo.png")
			|| !startupStuff->LoadMedia(texture_2, "10_color_keying/background.png")
			|| !startupStuff->LoadMedia(texture_3, "11_clip_rendering_and_sprite_sheets/dots.png")
			|| !startupStuff->LoadMedia(texture_4, "12_color_modulation/colors.png")
			|| !startupStuff->LoadMedia(texture_5, "13_alpha_blending/fadeout.png", SDL_BLENDMODE_BLEND)
			|| !startupStuff->LoadMedia(texture_animated, "14_animated_sprites_and_vsync/foo.png")
			|| !startupStuff->LoadMedia(texture_rotated, "15_rotation_and_flipping/arrow.png")
			|| !startupStuff->LoadMedia(buttonSprite, "17_mouse_events/button.png")
			|| !startupStuff->LoadMedia(pressTexture, "18_key_states/press.png")
			|| !startupStuff->LoadMedia(upTexture, "18_key_states/up.png")
			|| !startupStuff->LoadMedia(downTexture, "18_key_states/down.png")
			|| !startupStuff->LoadMedia(leftTexture, "18_key_states/left.png")
			|| !startupStuff->LoadMedia(rightTexture, "18_key_states/right.png")
			|| !startupStuff->LoadMedia(joystick_Texture, "19_gamepads_and_joysticks/arrow.png")
			|| !startupStuff->LoadMusic("21_sound_effects_and_music/beat.wav", music)
			|| !startupStuff->LoadSFX("21_sound_effects_and_music/scratch.wav", scratch)
			|| !startupStuff->LoadSFX("21_sound_effects_and_music/high.wav", high)
			|| !startupStuff->LoadSFX("21_sound_effects_and_music/medium.wav", medium)
			|| !startupStuff->LoadSFX("21_sound_effects_and_music/low.wav", low)
			|| !startupStuff->LoadMedia(audio_Texture, "21_sound_effects_and_music/prompt.png")
			|| !startupStuff->LoadMedia(dotTexture, "26_motion/dot.bmp"))
		{
			printf("Failed to load media!\n");
		}
		else
		{
#ifdef SDL_TTF_MAJOR_VERSION 
			if (!startupStuff->LoadText(gFont, "16_true_type_fonts/lazy.ttf", "Hello World", { 0, 0, 0 }, 60, texture_text))
			{
				printf("Failed to render text texture!\n");
			}
			if (!startupStuff->LoadText(gFont2, "22_timing/lazy.ttf", "Press Enter to Reset Start Time", { 255, 0, 0 }, 20, prompt_Texture))
			{
				printf("Failed to render text texture!\n");
			}
			if (!startupStuff->LoadText(gFont2, "22_timing/lazy.ttf", "Press P to Pause or Unpause the Timer", { 255, 0, 0 }, 20, pause_PromptTexture))
			{
				printf("Failed to render text texture!\n");
			}
			if (!startupStuff->LoadText(gFont2, "22_timing/lazy.ttf", "Press Q to Start or Stop the Timer", { 255, 0, 0 }, 20, start_PromptTexture))
			{
				printf("Failed to render text texture!\n");
			}
			if (!startupStuff->LoadText(gFont2, "22_timing/lazy.ttf", "Collider Check", { 0, 255, 0 }, 20, collidePrompt_Texture))
			{
				printf("Failed to render text texture!\n");
			}
#endif

			bool quit = false;
			SDL_Event e;

			Uint8 r = 255;
			Uint8 g = 255;
			Uint8 b = 255;
			Uint8 a = 255;

			int frame = 0;

			double degrees = 0;

			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			button[0].SetPosition(0, 120);
			button[1].SetPosition(SCREEN_WIDTH - BUTTON_WIDTH / 4, 120);
			button[2].SetPosition(120, SCREEN_HEIGHT - BUTTON_HEIGHT / 4 - 50);
			button[3].SetPosition(SCREEN_WIDTH - BUTTON_WIDTH / 4 - 120, SCREEN_HEIGHT - BUTTON_HEIGHT / 4 - 50);

			Texture_Mine* currentTexture = NULL;

			int xDir = 0;
			int yDir = 0;

			//Current time start time
			Uint32 startTime = 0;

			//In memory text stream
			std::stringstream timeText;

			//Start Stop Pause Timer
			Timer timer;
			std::stringstream timeText2;

			//Frames Per Second Timer
			Timer fpsTimer;
			std::stringstream fpsText;

			//Start Counting Frames per second
			int countedFrames = 0;
			fpsTimer.start();

			//Moving Dot
			Dot dot(20,20);

			//Dot To Collide With
			Dot collideDot(100, 100);

			//Wall for Collision
			SDL_Rect wall = { 660, 500, 200, 200 };

			while (!quit)
			{
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
							//Increase red
						case SDLK_r:
							r += 32;
							break;

							//Increase green
						case SDLK_g:
							g += 32;
							break;

							//Increase blue
						case SDLK_b:
							b += 32;
							break;

							//Decrease red
						case SDLK_e:
							r -= 32;
							break;

							//Decrease green
						case SDLK_f:
							g -= 32;
							break;

							//Decrease blue
						case SDLK_v:
							b -= 32;
							break;

							//Decrease alpha
						case SDLK_s:
							a -= 32;
							break;

							//Increase alpha
						case SDLK_a:
							a += 32;
							break;

							//Increase degrees
						case SDLK_l:
							degrees += 10;
							break;

							//Decrease degrees
						case SDLK_k:
							degrees -= 10;
							break;

							//Play High Sound
						case SDLK_1:
							Mix_PlayChannel(-1, high, 0);
							break;

							//Play Medium Sound
						case SDLK_2:
							Mix_PlayChannel(-1, medium, 0);
							break;

							//Play Low Sound
						case SDLK_3:
							Mix_PlayChannel(-1, low, 0);
							break;

							//Play Scratch Sound
						case SDLK_4:
							Mix_PlayChannel(-1, scratch, 0);
							break;

						case SDLK_9:
							//If there is no music playing
							if (Mix_PlayingMusic() == 0)
							{
								Mix_PlayMusic(music, -1);
							}
							//If music is being played
							else
							{
								//If music is paused
								if (Mix_PausedMusic() == 1)
								{
									//Resume Music
									Mix_ResumeMusic();
								}
								//If the music is playing
								else
								{
									//Pause the music
									Mix_PauseMusic();
								}
							}
							break;

						case SDLK_0:
							//Stop the music
							Mix_HaltMusic();
							break;

						case SDLK_RETURN:
							//Reset start time
							startTime = SDL_GetTicks();
							break;

							//Pause Music
						case SDLK_p:
							if (timer.isPaused())
							{
								timer.unpause();
							}
							else
							{
								timer.pause();
							}
							break;

							//Start/Stop
						case SDLK_q:
							if (timer.isStarted())
							{
								timer.stop();
							}
							else
							{
								timer.start();
							}
							break;
						}
					}
					//Joystick events
					else if (e.type == SDL_JOYAXISMOTION)
					{
						// Motion on Controller 0
						if (e.jaxis.which == 0)
						{
							//X axis motion on Contoller 0
							if (e.jaxis.axis == 0)
							{
								//Left of dead zone
								if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
								{
									xDir = -1;
								}
								//Right of dead zone
								else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
								{
									xDir = 1;
								}
								else
								{
									xDir = 0;
								}
							}
							//Y axis motion on Controller 0
							else if (e.jaxis.axis == 1)
							{
								//Below of dead zone
								if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
								{
									yDir = -1;
								}
								//Above of dead zone
								else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
								{
									yDir = 1;
								}
								else
								{
									yDir = 0;
								}
							}
						}
					}
					//Joystick button press
					else if (e.type == SDL_JOYBUTTONDOWN)
					{
						//Use Game Controller
						if (startupStuff->gameController != NULL)
						{
							//Play rumble at 75% strength for 500 milliseconds
							if (SDL_GameControllerRumble(startupStuff->gameController, 0xFFFF * 3 / 4, 0xFFFF * 3 / 4, 500) != 0)
							{
								printf("Warning: Unable to play game contoller rumble! %s\n", SDL_GetError());
							}
						}
						else if (startupStuff->joyHaptic != NULL)
						{
							if (SDL_HapticRumblePlay(startupStuff->joyHaptic, 0.75, 500) != 0)
							{
								printf("Warning: Unable to play joystick rumble! %s\n", SDL_GetError());
							}
						}
					}

					for (int i = 0; i < TOTAL_BUTTONS; ++i)
					{
						button[i].HandleEvent(&e);
					}

					dot.handleEvent(e);
				}

				//Set Texture based on current keyState
				const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
				if (currentKeyState[SDL_SCANCODE_UP])
				{
					currentTexture = &upTexture;
				}
				else if (currentKeyState[SDL_SCANCODE_DOWN])
				{
					currentTexture = &downTexture;
				}
				else if (currentKeyState[SDL_SCANCODE_LEFT])
				{
					currentTexture = &leftTexture;
				}
				else if (currentKeyState[SDL_SCANCODE_RIGHT])
				{
					currentTexture = &rightTexture;
				}
				else
				{
					currentTexture = &pressTexture;
				}

				//Set text to be rendered
				timeText.str("");
				timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime;

				//Render Text
				if (!timeTextTexture.LoadFromRenderededText(timeText.str().c_str(), { 255, 0, 0 }, gFont2, startupStuff->renderer))
				{
					printf("Unable to render time texture!\n");
				}

				timeText2.str("");
				timeText2 << "Seconds since start time " << (timer.getTicks() / 1000.f);

				if(!timerTextTexture2.LoadFromRenderededText(timeText2.str().c_str(), { 255, 0, 0 }, gFont2, startupStuff->renderer))
				{
					printf("Unable to render time texture!\n");
				}

				//Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				fpsText.str("");
				fpsText << "Average Frames Per Second " << avgFPS;

				if(!fpsTimer_Texture.LoadFromRenderededText(fpsText.str().c_str(), { 255, 0, 0 }, gFont2, startupStuff->renderer))
				{
					printf("Unable to render time texture!\n");
				}

				//dot.move(wall);
				std::vector<SDL_Rect> multipleCollider = collideDot.getColliders();
				multipleCollider.push_back(wall);
				//dot.move(multipleCollider);

				dot.move(wall, collideDot.getColliderCircle());

				SDL_SetRenderDrawColor(startupStuff->renderer, 0, 0, 0, 255);
				SDL_RenderClear(startupStuff->renderer);

				audio_Texture.RenderRotate(640, SCREEN_HEIGHT / 2 - audio_Texture.GetHeight() / 6, 3, startupStuff->renderer);

				texture_2.Render(0, 0, startupStuff->renderer, false);
				texture_1.Render(420, 200, startupStuff->renderer, false);

				texture_3.Render(SCREEN_WIDTH / 2 - texture_3.GetWidth() / 2, SCREEN_HEIGHT / 2 - texture_3.GetHeight() / 2, startupStuff->renderer, false);

				texture_3.Render(0, 0, startupStuff->renderer, &texture_3.clipRects[0]);
				texture_3.Render(SCREEN_WIDTH - texture_3.clipRects[1].w, 0, startupStuff->renderer, &texture_3.clipRects[1]);
				texture_3.Render(0, SCREEN_HEIGHT - texture_3.clipRects[2].h, startupStuff->renderer, &texture_3.clipRects[2]);
				texture_3.Render(SCREEN_WIDTH - texture_3.clipRects[3].w, SCREEN_HEIGHT - texture_3.clipRects[3].h, startupStuff->renderer, &texture_3.clipRects[3]);

				texture_4.SetColor(r, g, b);
				texture_4.Render(SCREEN_WIDTH / 2 - 50, 0, 100, 100, startupStuff->renderer);

				texture_5.SetAlpha(a);
				texture_5.Render(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 100, 120, 100, startupStuff->renderer);

				texture_animated.Render(100, 120, startupStuff->renderer, &texture_animated.animatedRects[frame / 16]);

				texture_rotated.RenderRotate(500, 250, 3, startupStuff->renderer, NULL, degrees, NULL, flipType);

#ifdef  SDL_TTF_MAJOR_VERSION

				texture_text.Render(150, 150, startupStuff->renderer, false);

#endif
				for (int i = 0; i < TOTAL_BUTTONS; i++)
				{
					button[i].Render(&buttonSprite, startupStuff->renderer);
				}

				currentTexture->RenderRotate(375, 0, 4, startupStuff->renderer);

				// conversion Radians to degree
				double joystickAngle = atan2(yDir, xDir) * 180 / M_PI;

				if (xDir == 0 && yDir == 0)
				{
					joystickAngle = 0;
				}

				joystick_Texture.RenderRotate(0, 250, 3, startupStuff->renderer, NULL, joystickAngle);

				prompt_Texture.Render(600, 0, startupStuff->renderer, false);
				timeTextTexture.Render(500, 20, startupStuff->renderer, false);

				start_PromptTexture.Render(0, 600, startupStuff->renderer, false);
				pause_PromptTexture.Render(0, 620, startupStuff->renderer, false);
				timerTextTexture2.Render(5, 640, startupStuff->renderer, false);

				fpsTimer_Texture.Render(5, 685, startupStuff->renderer, false);

				SDL_SetRenderDrawColor(startupStuff->renderer, 255, 0, 100, 255);
				SDL_RenderFillRect(startupStuff->renderer, &wall);

				collidePrompt_Texture.Render(670, 550, startupStuff->renderer, false);

				//dot.render(dotTexture, startupStuff->renderer);
				//collideDot.render(dotTexture, startupStuff->renderer);

				dot.renderCicle(dotTexture, startupStuff->renderer);
				collideDot.renderCicle(dotTexture, startupStuff->renderer);

				SDL_RenderPresent(startupStuff->renderer);
				++countedFrames;

				frame++;
				if (frame / 16 > 3)
				{
					frame = 0;
				}
			}
		}
	}
	close();
	return 0;
}