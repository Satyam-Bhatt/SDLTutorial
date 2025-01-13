//// This code does 
//// - Tiling of a level
//
//#include "ColorKeying_Mine/Texture_Mine.h"
//#include "ColorKeying_Mine/CommonVariables.h"
//#include "StartupStuff.h"
//#include "MouseEvents_h_cpp/Button.h"
//#include "Timer.h"
//#include "Dot.h"
//#include <fstream>
//#include "BitmapFont.h"
//#include "DataStream.h"
//#include <SDL_thread.h>
//#include <SDL_opengl.h>
//#include <GL\GLU.h>
//#define SDL_TTF_MAJOR_VERSION
//
//StartupStuff* startupStuff = new StartupStuff();
//
//TTF_Font* gFont = NULL, * gFont2 = NULL;
//
//Texture_Mine bitMapRender, streamingTexture, targetTexture, dotTexture;
//
//BitmapFont texture_text;
//
//DataStream dataStream;
//
//Uint32 callback(Uint32 interval, void* param);
//
//int threadFunction(void* data);
//
////Our worker thread function
//int worker(void* data);
//
////Worker thread for spin
//int worker_Spin(void* data);
//
////Data access semaphore
//SDL_sem* dataLock = NULL;
//
////The "data buffer"
//int gdata = -1;
//
////Data access sping lock
//SDL_SpinLock dataLock_Spin = 0;
//
////The "data buffer"
//int data_Spin = -1;
//
////Our worker functions
//int producer(void * data);
//int consumer(void * data);
//void produce();
//void consume();
//
////The protective mutex
//SDL_mutex* gBufferLock = NULL;
//
////The conditions
//SDL_cond* gCanProduce = NULL;
//SDL_cond* gCanConsume = NULL;
//
////The data buffer
//int data_Mutex = -1;
//
//void close()
//{
//	dotTexture.Free();
//	dataStream.free();
//	texture_text.free();
//	targetTexture.Free();
//
//	bitMapRender.Free();
//
//	SDL_DestroySemaphore(dataLock);
//	dataLock = NULL;
//
//	SDL_DestroyMutex(gBufferLock);
//	gBufferLock = NULL;
//
//	SDL_DestroyCond(gCanProduce);
//	gCanProduce = NULL;
//	SDL_DestroyCond(gCanConsume);
//	gCanConsume = NULL;
//
//	TTF_CloseFont(gFont);
//	gFont = NULL;
//	TTF_CloseFont(gFont2);
//	gFont2 = NULL;
//
//	startupStuff->Free();
//	delete startupStuff;
//	startupStuff = nullptr;
//
//	TTF_Quit();
//	IMG_Quit();
//	SDL_Quit();
//	Mix_Quit();
//}
//
//Uint32 callback(Uint32 interval, void* param)
//{
//	 printf("Timer triggered! Message: %s\n", (char*)param);
//	//std::string* message = static_cast<std::string*>(param);
//	//printf("Timer triggered! Message: %s\n", message->c_str());
//	return 0;
//}
//
//int threadFunction(void* data)
//{
//	//Print incoming data
//	printf("Runnign thread with value = %d\n", int(data));
//	return 0;
//}
//
//int worker(void* data)
//{
//	printf("%s starting... \n", (char*)data);
//
//	//Pre thread random seeding
//	srand(SDL_GetTicks());
//
//	//Work 5 times
//	for (int i = 0; i < 5; ++i)
//	{
//		//Waiut randomly
//		SDL_Delay(16 + rand() % 32);
//	
//		//Lock
//		SDL_SemWait(dataLock);
//
//		//Print per work data
//		printf("%s gets %d\n", (char*)data, gdata);
//
//		//"Work"
//		gdata = rand() % 256;
//
//		//Print post work data
//		printf("%s sets %d\n\n", (char*)data, gdata);
//
//		//Unlock
//		SDL_SemPost(dataLock);
//
//		//Wait Randomly
//		SDL_Delay(16 + rand() % 640);
//	}
//
//	printf("%s finished\n", (char*)data);
//
//	if ((char*)data == "Thread A")
//	{
//		//Run the threads
//		srand(SDL_GetTicks());
//		SDL_Thread* threadA = SDL_CreateThread(worker_Spin, "Thread A", (void*)"Thread A");
//		SDL_Delay(16 + rand() % 32);
//		SDL_Thread* threadB = SDL_CreateThread(worker_Spin, "Thread B", (void*)"Thread B");
//	}
//
//	return 0;
//}
//
//int worker_Spin(void* data)
//{
//	printf("%s starting SPIN... \n", (char*)data);
//
//	//Pre thread random seeding
//	srand(SDL_GetTicks());
//
//	//Work 5 times
//	for (int i = 0; i < 5; ++i)
//	{
//		//Wait randomly
//		SDL_Delay(16 + rand() % 32);
//
//		//Lock
//		SDL_AtomicLock(&dataLock_Spin);
//
//		//Print per work data
//		printf("%s gets %d\n", (char*)data, data_Spin);
//
//		//"Work"
//		data_Spin = rand() % 256;
//
//		//Print post work data
//		printf("%s sets %d\n\n", (char*)data, data_Spin);
//
//		//Unlock
//		SDL_AtomicUnlock(&dataLock_Spin);
//
//		//Wait Randomly
//		SDL_Delay(16 + rand() % 640);
//	}
//
//	printf("%s finished  SPIN\n", (char*)data);
//
//	if ((char*)data == "Thread A")
//	{
//		srand(SDL_GetTicks());
//		SDL_Thread* threadA = SDL_CreateThread(producer, "Thread A", (void*)"Thread A");
//		SDL_Delay(16 + rand() % 32);
//		SDL_Thread* threadB = SDL_CreateThread(consumer, "Thread B", (void*)"Thread B");
//	}
//
//	return 0;
//}
//
//int producer(void* data)
//{
//	printf("\nProducer started....\n");
//
//	//See thread random
//	srand(SDL_GetTicks());
//
//	//Produce 5 times
//	for (int i = 0; i < 5; ++i)
//	{
//		//Wait randomly
//		SDL_Delay(rand() % 1000);
//
//		//Produce
//		produce();
//	}
//
//	printf("\nProducer finished\n");
//	return 0;
//}
//
//int consumer(void* data)
//{
//	printf("\nConsumer started....\n");
//
//	//See thread random
//	srand(SDL_GetTicks());
//
//	//Consume 5 times
//	for (int i = 0; i < 5; ++i)
//	{
//		//Wait randomly
//		SDL_Delay(rand() % 1000);
//
//		//Consume
//		consume();
//	}
//
//	printf("\nConsumer finished\n");
//	return 0;
//}
//
//void produce()
//{
//	//Lock
//	SDL_LockMutex(gBufferLock);
//
//	//if the buffer is full
//	if (data_Mutex != -1)
//	{
//		//Wait for buffer to be cleared
//		printf("\nProducer encountered full buffer, waiting for consumer to empty buffer...\n");
//		SDL_CondWait(gCanProduce, gBufferLock);
//	}
//
//	//Fill and show buffer
//	data_Mutex = rand() % 255;
//	printf("\nProduced %d\n", data_Mutex);
//
//	//Unlock
//	SDL_UnlockMutex(gBufferLock);
//
//	//Signal consumer
//	SDL_CondSignal(gCanConsume);
//}
//
//void consume()
//{
//	//Lock
//	SDL_LockMutex(gBufferLock);
//
//	//If the buffer is empty
//	if (data_Mutex == -1)
//	{
//		//Wait for buffer to be filled
//		printf("\nConsumer encountered empty buffer, waiting for producer to produce data...\n");
//		SDL_CondWait(gCanConsume, gBufferLock);
//	}
//
//	//Show and empty buffer
//	printf("\nConsumed %d\n", data_Mutex);
//	data_Mutex = -1;
//
//	//Unlock
//	SDL_UnlockMutex(gBufferLock);
//
//	//Signal producer
//	SDL_CondSignal(gCanProduce);
//}
//
//int main(int argc, char* args[])
//{
//	if (!startupStuff->init())
//	{
//		printf("Failed to initialize!\n");
//	}
//	else
//	{
//		if (!startupStuff->LoadMedia_TextureManipulation(bitMapRender, "40_texture_manipulation/foo.png")
//			|| !texture_text.buildFont("41_bitmap_fonts/lazyfont.png", startupStuff->renderer, startupStuff->window)
//			|| !streamingTexture.createBlank(64, 205, startupStuff->renderer)
//			|| !dataStream.loadMedia()
//			|| !targetTexture.createBlank(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_TEXTUREACCESS_TARGET, startupStuff->renderer)
//			|| !startupStuff->LoadMedia(dotTexture, "44_frame_independent_movement/dot.bmp"))
//		{
//			printf("Failed to load media!\n");
//		}
//		else
//		{
//#ifdef SDL_TTF_MAJOR_VERSION 
//			//if (!startupStuff->LoadText(gFont, "16_true_type_fonts/lazy.ttf", "Hello World", { 0, 0, 0 }, 60, texture_text))
//			//{
//			//	printf("Failed to render text texture!\n");
//			//}
//#endif
//			bool quit = false;
//			SDL_Event e;;
//
//			double angle = 0;
//			SDL_Point screenCenter = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
//
//			Dot dot(20,20);
//			Timer frameTimer;
//
//			//1- const char* point = "Hello from the timer!";
//
//			std::string message = "Hello from the timer!";
//			//std::string* point = &message;
//
//			const char* point = message.c_str();
//
//			// Add a timer to be triggered every 1000 ms (1 second)
//			SDL_TimerID timerID = SDL_AddTimer(1000, callback, (void*)point);
//
//			//Run the thread
//			int data = 101;
//			SDL_Thread* threadID = SDL_CreateThread(threadFunction, "LazyThread", (void*)data);
//
//			dataLock = SDL_CreateSemaphore(1);
//
//			//Create the mutex
//			gBufferLock = SDL_CreateMutex();
//
//			//Create conditions
//			gCanProduce = SDL_CreateCond();
//			gCanConsume = SDL_CreateCond();
//
//			//Run the threads
//			srand(SDL_GetTicks());
//			SDL_Thread * threadA = SDL_CreateThread(worker, "Thread A", (void*)"Thread A");
//			SDL_Delay(16 + rand() % 32);
//			SDL_Thread* threadB = SDL_CreateThread(worker, "Thread B", (void*)"Thread B");
//
//			while (!quit)
//			{
//				bool renderText = false;
//
//				while (SDL_PollEvent(&e) != 0)
//				{
//					if (e.type == SDL_QUIT)
//					{
//						quit = true;
//					}
//
//					//Key press events
//					else if (e.type == SDL_KEYDOWN)
//					{
//						switch (e.key.keysym.sym)
//						{
//
//						}
//					}
//
//					dot.handleEvent(e);
//
//				}
//
//				angle += 1;
//				if (angle > 360)
//				{
//					angle -= 360;
//				}
//
//				float timeStep = frameTimer.getTicks() / 1000.f;
//				
//				dot.move_FrameIndependent(timeStep);
//
//				frameTimer.start();
//
//				//Set self as render target
//				targetTexture.SetAsRenderTarget(startupStuff->renderer);
//
//				//Only draw if window is not minimized
//				//if (!startupStuff->isMinimized())
//				//{
//				SDL_SetRenderDrawColor(startupStuff->renderer, 255, 255, 0, 255);
//				SDL_RenderClear(startupStuff->renderer);
//
//				bitMapRender.Render((SCREEN_WIDTH - bitMapRender.GetWidth()) / 2, (SCREEN_HEIGHT - bitMapRender.GetHeight()) / 2,
//					startupStuff->renderer, false);
//
//				texture_text.renderText(0, 0, "AAAaaaaBBBbbbcasomdwew\nasdawd\nnn  asdasd \nsjkdn", startupStuff->renderer);
//
//				streamingTexture.lockTexture();
//				streamingTexture.copyRawPixels32(dataStream.getBuffer());
//				streamingTexture.unlockTexture();
//
//				streamingTexture.Render(0, 0, startupStuff->renderer, false);
//
//				//Render red filled quad
//				SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
//				SDL_SetRenderDrawColor(startupStuff->renderer, 0xFF, 0x00, 0x00, 0xFF);
//				SDL_RenderFillRect(startupStuff->renderer, &fillRect);
//
//				//Render green outlined quad
//				SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
//				SDL_SetRenderDrawColor(startupStuff->renderer, 0x00, 0xFF, 0x00, 0xFF);
//				SDL_RenderDrawRect(startupStuff->renderer, &outlineRect);
//
//				//Draw blue horizontal line
//				SDL_SetRenderDrawColor(startupStuff->renderer, 0x00, 0x00, 0xFF, 0xFF);
//				SDL_RenderDrawLine(startupStuff->renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
//
//				//Draw vertical line of yellow dots
//				SDL_SetRenderDrawColor(startupStuff->renderer, 0xFF, 0xFF, 0x00, 0xFF);
//				for (int i = 0; i < SCREEN_HEIGHT; i += 4)
//				{
//					SDL_RenderDrawPoint(startupStuff->renderer, SCREEN_WIDTH / 2, i);
//				}
//
//				dot.render(dotTexture, startupStuff->renderer);
//
//				//Reset Render target
//				SDL_SetRenderTarget(startupStuff->renderer, NULL);
//
//				//Show rendered to texture
//				//targetTexture.Render(0, 0, startupStuff->renderer, false);
//				targetTexture.RenderRotate(0, 0, 1, startupStuff->renderer, NULL, angle, &screenCenter);
//
//				SDL_RenderPresent(startupStuff->renderer);
//				//}
//			}
//			SDL_RemoveTimer(timerID);
//			SDL_WaitThread(threadID, NULL);
//			SDL_WaitThread(threadA, NULL);
//			SDL_WaitThread(threadB, NULL);
//		}
//	}
//
//	close();
//	return 0;
//}