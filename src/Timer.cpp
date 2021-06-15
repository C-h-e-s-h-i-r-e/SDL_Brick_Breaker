#include <SDL2/SDL.h>

#include "Timer.h"

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;

    paused = false;
    running = false;
}

void Timer::start()
{
    running = true;
    paused = false;
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop()
{
    paused = false;
    running = false;

    startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause()
{
    if (!paused)
    {
        paused = true;

        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause()
{
    if (paused && running)
    {
        paused = false;

        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

uint32_t Timer::getTicks()
{
    uint32_t time = 0;

    if (running)
        time = paused ? pausedTicks : SDL_GetTicks() - startTicks;

    return time;
}