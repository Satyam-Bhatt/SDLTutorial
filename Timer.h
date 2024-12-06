#include <SDL.h>
#pragma once

class Timer
{
public:
	//Initialize Variables
	Timer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Get the timer's time
	Uint32 getTicks();

	//Status of the timer
	bool isPaused();
	bool isStarted();

private:
	//The clock time when the timer starts
	Uint32 startTicks;

	//The ticks stored when the timer was paused
	Uint32 pausedTicks;

	//The timer status
	bool paused;
	bool started;
};

