#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "GameManager.h"
#include "Window.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_MAX_FPS 60

//Mix_Music *gMusic = NULL;

int main(int argc, char ** argv)
{

    Window window("Brick Breaker", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_MAX_FPS);
    GameManager manager(&window);

    // Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );

    // gMusic = Mix_LoadMUS( "src/bmusic.wav" );

    // Mix_FreeMusic( gMusic );
	// gMusic = NULL;

    // Mix_PlayMusic( gMusic, -1 );

    // SDL_Event e;

    // 				while( SDL_PollEvent( &e ) != 0 )
	// 			{
	// 				//Handle key press
	// 				if( e.type == SDL_KEYDOWN )
	// 				{
	// 					switch( e.key.keysym.sym )
	// 					{
	// 						case SDLK_9:
    //                         printf("9 clicked");
	// 						//If there is no music playing
	// 						if( Mix_PlayingMusic() == 0 )
	// 						{
	// 							//Play the music
	// 							Mix_PlayMusic( gMusic, -1 );
	// 						}
	// 						//If music is being played
	// 						else
	// 						{
	// 							//If the music is paused
	// 							if( Mix_PausedMusic() == 1 )
	// 							{
	// 								//Resume the music
	// 								Mix_ResumeMusic();
	// 							}
	// 							//If the music is playing
	// 							else
	// 							{
	// 								//Pause the music
	// 								Mix_PauseMusic();
	// 							}
	// 						}
	// 						break;
							
	// 						case SDLK_0:
    //                         printf("0 clicked");
	// 						//Stop the music
	// 						Mix_HaltMusic();
	// 						break;
	// 					}
	// 				}
	// 			}

    manager.runGame();

    window.cleanupAndExit();
    
    return 0;
}
