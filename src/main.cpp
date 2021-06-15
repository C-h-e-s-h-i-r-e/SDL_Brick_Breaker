#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "GameManager.h"
#include "Window.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_MAX_FPS 60

int main(int argc, char ** argv)
{

    Window window("Brick Breaker", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_MAX_FPS);
    GameManager manager(&window);

    manager.runGame();

    window.cleanupAndExit();
    
    return 0;
}
