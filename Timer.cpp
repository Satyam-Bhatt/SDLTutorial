#include "Timer.h"


Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void Timer::stop()
{
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

void Timer::pause()
{
	if (started && !paused)
	{
		paused = true;
		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Timer::unpause()
{
	if (paused && started)
	{
		paused = false;

		//Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	Uint32 time = 0;

	//If the timer is running
	if (started)
	{
		if(paused)
		{
			time = pausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

bool Timer::isPaused()
{
	return paused && started;
}

bool Timer::isStarted()
{
	return started;
}