#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <vector>
#include <SDL2/SDL_mixer.h>

#include "Window.h"
#include "Entity.h"
#include "Ball.h"
#include "Mods.h"

enum GameState
{
    STATE_MENU = 0,
    STATE_PLAYING = 1,
    STATE_WINNER = 2,
    STATE_HOWTOPLAY = 3,
    STATE_CREDITS = 4,
    STATE_LEVELS = 5
};

class GameManager
{
    public:
        GameManager(Window* window);

        void runGame();

        void quit() { _quit = true; }
        void setState(int state);

        void initGame(bool fresh);

        Window* getWindow() { return window; }

		void addEntity(Entity* e);

        void listenForQuit();

        void printLevels();

        void printC();

        void printHow();

    private:
        Window* window;
        SDL_Event event;

        Ball* ball;
        Entity* paddle;
        Mods* mod;
        Mods* bonus_life;


        SDL_Texture* bgTexture;
        SDL_Texture* bg2Texture;
        SDL_Texture* bgGameTexture;

        Mix_Chunk* ballHitSound = NULL;
        Mix_Chunk* brickBreakSound = NULL;

        bool powerUpActive;

        int powerupTimer;
        int randNum;
        int randPos;
        int downNum;
        int upNum;

        bool isPressed = false;
		int currentLevel;

        bool showMessage;
        std::string message;

        int maxBricks;

        int bricksLeft;

        int totalBricksDestroyed;

        int remainingLives;

        bool levelOver;

        int calcScore();

        int saveLife();

        void gameTick();

        bool _quit;

        int currentState;

        std::vector<Entity*> entities;
};

#endif