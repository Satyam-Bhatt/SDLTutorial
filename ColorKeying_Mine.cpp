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
// - Collision With Rects
// - Collision Per-Pixel
// - Collision Circle and Square
// - Camera Scrolling
// - Scrolling Background
// - Enter Text
// - Save and Load

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

Texture_Mine fpsTimer_Texture, dotTexture, collidePrompt_Texture, background_Texture, scrollingBackground_Texture, inputText_Texture;

Texture_Mine buttonSprite;
Button button[TOTAL_BUTTONS];

//Key State Textures
Texture_Mine pressTexture, upTexture, downTexture, leftTexture, rightTexture, dataTextures[TOTAL_DATA];

//Music
Mix_Music* music = NULL;

//Sound Effects
Mix_Chunk* scratch = NULL, * high = NULL, * medium = NULL, * low = NULL;

//Data Points
Sint32 gData[TOTAL_DATA];

//Recording/playback callbacks
void audioRecordingCallback(void* userdata, Uint8* stream, int len);
void audioPlaybackCallback(void* userdata, Uint8* stream, int len);

//Prompt Audio Texture
Texture_Mine promptAudioTexture;

//Texture to show recording device names
Texture_Mine recordingDeviceTexture[MAX_RECORDING_DEVICES];

//Number of available devices
int recordingDeviceCount = 0;

//Received audio spec
SDL_AudioSpec receivedRecordingSpec;
SDL_AudioSpec receivedPlaybackSpec;

//Recording data buffer
Uint8* recordingBuffer = NULL;

//Size of data buffer
Uint32 bufferByteSize = 0;

//Position in data buffer
Uint32 bufferBytePosition = 0;

//Maximum position in data buffer for recording
Uint32 bufferByteMaxPosition = 0;

void close()
{
	//open data for writing
	SDL_RWops* file = SDL_RWFromFile("33_file_reading_and_writing/nums.bin", "w+b");

	if (file != NULL)
	{
		//save data
		for (int i = 0; i < TOTAL_DATA; ++i)
		{
			SDL_RWwrite(file, &gData[i], sizeof(Sint32), 1);
		}
		//close file handler
		SDL_RWclose(file);
	}
	else
	{
		printf("Error: Unable to save file! %s\n", SDL_GetError());
	}

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
	background_Texture.Free();
	scrollingBackground_Texture.Free();
	inputText_Texture.Free();
	promptAudioTexture.Free();
	for (int i = 0; i < TOTAL_DATA; ++i)
	{
		dataTextures[i].Free();
	}
	for (int i = 0; i < MAX_RECORDING_DEVICES; i++)
	{
		recordingDeviceTexture[i].Free();
	}

	//Free playback audio
	if (recordingBuffer != NULL)
	{
		delete[] recordingBuffer;
		recordingBuffer = NULL;
	}

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

void audioRecordingCallback(void* userdata, Uint8* stream, int len)
{
	//Copy audio from stream
	memcpy(&recordingBuffer[bufferBytePosition], stream, len);

	//Move along buffer
	bufferBytePosition += len;
}

void audioPlaybackCallback(void* userdata, Uint8* stream, int len)
{
	//Copy audio to stream
	memcpy(stream, &recordingBuffer[bufferBytePosition], len);

	//Move along buffer
	bufferBytePosition += len;
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
			|| !startupStuff->LoadMedia(dotTexture, "26_motion/dot.bmp")
			|| !startupStuff->LoadMedia(background_Texture, "30_scrolling/bg.png")
			|| !startupStuff->LoadMedia(scrollingBackground_Texture, "31_scrolling_backgrounds/bg.png"))
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
			if (!startupStuff->LoadText_Save(gFont2, "22_timing/lazy.ttf", "Time: ", { 255, 0, 0 }, 20, dataTextures, gData))
			{
				printf("Failed to render text texture!\n");
			}
			if (!startupStuff->LoadText(gFont2, "22_timing/lazy.ttf", "Audio Devices: ", { 255, 0, 0 }, 20, pause_PromptTexture))
			{
				printf("Failed to render text texture!\n");
			}
			if (!startupStuff->LoadAudio(gFont2, { 255,0,255,255 }, recordingDeviceTexture, recordingDeviceCount))
			{
				printf("Failed to load audio device + Textures!\n");
			}
			if (!startupStuff->LoadText(gFont2, "22_timing/lazy.ttf", "Select Your recording Device:  ", { 255, 255, 0 }, 20, promptAudioTexture))
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
			Dot dot(20, 20);

			//Dot To Collide With
			Dot collideDot(100, 100);

			//Wall for Collision
			SDL_Rect wall = { 660, 500, 200, 200 };
			SDL_Rect falkeWall = { 660, 500, 200, 200 };

			//The camera area
			SDL_Rect camera = { 0,0, SCREEN_WIDTH + SCREEN_EXTENTION, SCREEN_HEIGHT + SCREEN_EXTENTION };

			//Offset for Background
			int bgOffset = 0;

			//Input Text
			SDL_Color textColor = { 0,0,0,0xFF };

			//The current input text
			std::string inputText = "Enter Text Here";
			inputText_Texture.LoadFromRenderededText(inputText, textColor, gFont2, startupStuff->renderer);

			//Enable text input
			SDL_StartTextInput();

			//Text rendering color
			SDL_Color textColor_Main = { 0, 0, 0, 0xFF };
			SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };

			//Current input point
			int currentData = 0;

			//Set default recording state
			RecordingState currentState = SELECTING_DEVICE;

			//Audio Device IDs
			SDL_AudioDeviceID recordingDeviceId = 0;
			SDL_AudioDeviceID playbackDeviceId = 0;

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

						case SDLK_UP:
							//Rerender previous entry input point
							dataTextures[currentData].LoadFromRenderededText(std::to_string(gData[currentData]), textColor, gFont2, startupStuff->renderer);
							--currentData;
							if (currentData < 0)
							{
								currentData = TOTAL_DATA - 1;
							}
							//Rerender current entry input point
							dataTextures[currentData].LoadFromRenderededText(std::to_string(gData[currentData]), highlightColor, gFont2, startupStuff->renderer);
							break;

						case SDLK_DOWN:
							//Rerender previous entry input point
							dataTextures[currentData].LoadFromRenderededText(std::to_string(gData[currentData]), textColor, gFont2, startupStuff->renderer);
							++currentData;
							if (currentData == TOTAL_DATA)
							{
								currentData = 0;
							}

							//Rerender current entry input point
							dataTextures[currentData].LoadFromRenderededText(std::to_string(gData[currentData]), highlightColor, gFont2, startupStuff->renderer);
							break;

						case SDLK_LEFT:
							--gData[currentData];
							dataTextures[currentData].LoadFromRenderededText(std::to_string(gData[currentData]), highlightColor, gFont2, startupStuff->renderer);
							break;

						case SDLK_RIGHT:
							++gData[currentData];
							dataTextures[currentData].LoadFromRenderededText(std::to_string(gData[currentData]), highlightColor, gFont2, startupStuff->renderer);
							break;
						}

						//Handle Backspace
						if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
						{
							//lop off character
							inputText.pop_back();
							renderText = true;
						}
						//Handle Copy
						else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() && KMOD_CTRL)
						{
							SDL_SetClipboardText(inputText.c_str());
						}
						//Handle Paste
						else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() && KMOD_CTRL)
						{
							//Copy text from temporary buffer
							char* tempText = SDL_GetClipboardText();
							inputText = tempText;
							SDL_free(tempText);

							renderText = true;
						}
					}
					//Special Text input events
					else if (e.type == SDL_TEXTINPUT)
					{
						//Not copy or pasing
						if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
						{
							//Append character
							inputText += e.text.text;
							renderText = true;
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

					//Do current state event handling
					switch (currentState)
					{
						//User is selecting recording device
					case SELECTING_DEVICE:
						//On Key Press
						if (e.type == SDL_KEYDOWN)
						{
							//Handle key press from 0 to 9
							if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9)
							{
								//Get selection index
								int index = e.key.keysym.sym - SDLK_0;

								//Index is valid
								if (index < recordingDeviceCount)
								{
									//Default Audio Spec
									SDL_AudioSpec desiredRecordingSpec;
									SDL_zero(desiredRecordingSpec);
									desiredRecordingSpec.freq = 44100;
									desiredRecordingSpec.format = AUDIO_F32;
									desiredRecordingSpec.channels = 2;
									desiredRecordingSpec.samples = 4096;
									desiredRecordingSpec.callback = audioRecordingCallback;

									//Open recording device
									recordingDeviceId = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(index, SDL_TRUE), SDL_TRUE, &desiredRecordingSpec, &receivedRecordingSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

									//Device failed to open
									if (recordingDeviceId == 0)
									{
										//Report Error
										printf("Failed to open recording device! SDL Error: %s", SDL_GetError());
										promptAudioTexture.LoadFromRenderededText("Failed to open recording device!", textColor, gFont2, startupStuff->renderer);
										currentState = ERROR;
									}
									//Device Opened Successfully
									else
									{
										//Default Audio Spec
										SDL_AudioSpec desiredPlayabackSpec;
										SDL_zero(desiredPlayabackSpec);
										desiredPlayabackSpec.freq = 44100;
										desiredPlayabackSpec.format = AUDIO_F32;
										desiredPlayabackSpec.channels = 2;
										desiredPlayabackSpec.samples = 4096;
										desiredPlayabackSpec.callback = audioPlaybackCallback;

										//Open playback device
										playbackDeviceId = SDL_OpenAudioDevice(NULL, SDL_FALSE, &desiredPlayabackSpec, &receivedPlaybackSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

										//Device Failed to open
										if (playbackDeviceId == 0)
										{
											//Report Error
											printf("Failed to open playback device! SDL Error: %s", SDL_GetError());
											promptAudioTexture.LoadFromRenderededText("Failed to open playback device!", textColor, gFont2, startupStuff->renderer);
											currentState = ERROR;
										}
										//Device Opened Successfully
										else
										{
											//Calculate per sample bytes
											int bytePerSample = receivedRecordingSpec.channels * (SDL_AUDIO_BITSIZE(receivedRecordingSpec.format) / 8);

											//Calculate bytes per second
											int bytesPerSecond = receivedRecordingSpec.freq * bytePerSample;

											//Calculate buffer size
											bufferByteSize = RECORDING_BUFFER_SECONDS * bytesPerSecond;

											//Calculate max buffer use
											bufferByteMaxPosition = MAX_RECORDING_SECONDS * bytesPerSecond;

											//Allocate and initialize byte buffer
											recordingBuffer = new Uint8[bufferByteSize];
											memset(recordingBuffer, 0, bufferByteSize);

											//Go on to next state
											promptAudioTexture.LoadFromRenderededText("Press 1 to record for 5 seconds.", textColor, gFont, startupStuff->renderer);
											currentState = STOPPED;
										}
									}
								}
							}
						}
						break;

						//User getting ready to record
					case STOPPED:
						if (e.type == SDL_KEYDOWN)
						{
							//Start Recording
							if (e.key.keysym.sym == SDLK_1)
							{
								//Go back to beginning of buffer
								bufferBytePosition = 0;

								//Start recording
								SDL_PauseAudioDevice(recordingDeviceId, SDL_FALSE);

								//Go on to next state
								promptAudioTexture.LoadFromRenderededText("Recording...", textColor, gFont, startupStuff->renderer);
								currentState = RECORDING;
							}
						}
						break;

						// User has finished recording
					case RECORDED:

						//On Key Press
						if (e.type == SDL_KEYDOWN)
						{
							//Start playback
							if (e.key.keysym.sym == SDLK_1)
							{
								//Go back to beginning of buffer
								bufferBytePosition = 0;

								//Start Playback
								SDL_PauseAudioDevice(playbackDeviceId, SDL_FALSE);

								//Go on to next state
								promptAudioTexture.LoadFromRenderededText("Playing...", textColor, gFont, startupStuff->renderer);
								currentState = PLAYBACK;
							}
							//Record again
							if (e.key.keysym.sym == SDLK_2)
							{
								//Reset the buffer
								bufferByteMaxPosition = 0;
								memset(recordingBuffer, 0, bufferByteSize);

								//Start Recording
								SDL_PauseAudioDevice(recordingDeviceId, SDL_FALSE);

								//Go on to next state
								promptAudioTexture.LoadFromRenderededText("Recording...", textColor, gFont, startupStuff->renderer);
								currentState = RECORDING;
							}
						}
						break;
					}
					dot.handleEvent(e);
				}

				//Updating recording
				if (currentState == RECORDING)
				{
					//Look Callback
					SDL_LockAudioDevice(recordingDeviceId);

					printf("Recording...%d :: max::%d\n", bufferBytePosition, bufferByteMaxPosition);

					//Finish Recording
					if (bufferBytePosition > bufferByteMaxPosition)
					{
						//Stop Recording Audio
						SDL_PauseAudioDevice(recordingDeviceId, SDL_TRUE);

						//Go on to next state
						promptAudioTexture.LoadFromRenderededText("Press 1 to play. Press 2 to record again", textColor, gFont, startupStuff->renderer);
						currentState = RECORDED;
					}

					//Unlock Callback
					SDL_UnlockAudioDevice(recordingDeviceId);
				}
				//Updating Playback
				else if (currentState == PLAYBACK)
				{
					//Look Callback
					SDL_LockAudioDevice(playbackDeviceId);

					//Finished Playback
					if (bufferBytePosition > bufferByteMaxPosition)
					{
						//Stop playing audio
						SDL_PauseAudioDevice(playbackDeviceId, SDL_TRUE);

						//Go on to next state
						promptAudioTexture.LoadFromRenderededText("Press 1 to play. Press 2 to record again", textColor, gFont, startupStuff->renderer);
						currentState = RECORDED;
					}

					//Unlock Callback
					SDL_UnlockAudioDevice(playbackDeviceId);
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

				if (renderText)
				{
					//Text is not empty
					if (inputText != "")
					{
						//Render new text
						if (!inputText_Texture.LoadFromRenderededText(inputText, textColor, gFont2, startupStuff->renderer))
						{
							printf("Unable to render text texture!\n");
						}
					}
					//Text is empty
					else
					{
						//Render Space Texture
						if (!inputText_Texture.LoadFromRenderededText(" ", textColor, gFont2, startupStuff->renderer))
						{
							printf("Unable to render text texture!\n");
						}
					}
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

				if (!timerTextTexture2.LoadFromRenderededText(timeText2.str().c_str(), { 255, 0, 0 }, gFont2, startupStuff->renderer))
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

				if (!fpsTimer_Texture.LoadFromRenderededText(fpsText.str().c_str(), { 255, 0, 0 }, gFont2, startupStuff->renderer))
				{
					printf("Unable to render time texture!\n");
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
				dot.move(falkeWall, collideDot.getColliderCircle());
				//-----------------------

				//-------- CAMERA ----------
				camera.x = dot.getPosX() - (SCREEN_WIDTH + SCREEN_EXTENTION) / 2;
				camera.y = dot.getPosY() - (SCREEN_HEIGHT + SCREEN_EXTENTION) / 2;

				if (camera.x > 0 && camera.y > 0)
				{
					falkeWall.x += camera.x;
					falkeWall.y += camera.y;
				}

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
					falkeWall.x = 660;
					falkeWall.x += camera.x;
				}
				if (camera.y > SCREEN_HEIGHT_CAMERA - camera.h)
				{
					camera.y = SCREEN_HEIGHT_CAMERA - camera.h;
					falkeWall.y = 500;
					falkeWall.y += camera.y;
				}

				SDL_SetRenderDrawColor(startupStuff->renderer, 255, 255, 0, 255);
				SDL_RenderClear(startupStuff->renderer);

				background_Texture.Render(0, 0, startupStuff->renderer, &camera);

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

				--bgOffset;
				if (bgOffset < -400)
				{
					bgOffset = 0;
				}

				scrollingBackground_Texture.Render(bgOffset, 580, 400, 140, startupStuff->renderer);
				scrollingBackground_Texture.Render(bgOffset + 400, 580, 400, 140, startupStuff->renderer);
				scrollingBackground_Texture.Render(bgOffset + 800, 580, 400, 140, startupStuff->renderer);

				start_PromptTexture.Render(0, 600, startupStuff->renderer, false);
				pause_PromptTexture.Render(0, 620, startupStuff->renderer, false);
				timerTextTexture2.Render(5, 640, startupStuff->renderer, false);

				fpsTimer_Texture.Render(5, 685, startupStuff->renderer, false);

				SDL_SetRenderDrawColor(startupStuff->renderer, 255, 0, 100, 255);
				SDL_RenderFillRect(startupStuff->renderer, &wall);

				collidePrompt_Texture.Render(670, 550, startupStuff->renderer, false);

				//dot.render(dotTexture, startupStuff->renderer);
				//collideDot.render(dotTexture, startupStuff->renderer);

				//dot.renderCicle(dotTexture, startupStuff->renderer);
				dot.renderCicleWithCamera(camera.x, camera.y, dotTexture, startupStuff->renderer);
				collideDot.renderCicle(dotTexture, startupStuff->renderer);

				inputText_Texture.Render(20, 550, startupStuff->renderer, false);

				for (int i = 0; i < TOTAL_DATA; ++i)
				{
					dataTextures[i].Render(400, 500 + i * 20, startupStuff->renderer, false);
				}

				promptAudioTexture.Render(0, 0, startupStuff->renderer, false);

				//User is selecting
				if (currentState == SELECTING_DEVICE)
				{
					//Render Device Names
					int yOffset = promptAudioTexture.GetHeight() * 2;

					for (int i = 0; i < recordingDeviceCount; ++i)
					{
						recordingDeviceTexture[i].Render(0, yOffset, startupStuff->renderer, false);
						yOffset += recordingDeviceTexture[i].GetHeight();
					}
				}

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
	//Disable text input
	SDL_StopTextInput();

	close();
	return 0;
}