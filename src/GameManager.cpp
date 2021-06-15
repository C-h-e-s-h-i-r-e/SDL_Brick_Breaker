#include <iostream>
#include <time.h>
#include <array>
#include <string>
#include "Brick.h"
#include "GameManager.h"
#include "Menu.h"
#include "Timer.h"
#include "levelLoader.h"



GameManager::GameManager(Window* window):
    window(window)
{
    currentState = STATE_MENU;
    _quit = false;
    srand(time(NULL));

    bgTexture = window->loadTexture("bg1.png");
    bg2Texture = window->loadTexture("bg2.png");
    bgGameTexture = window->loadTexture("bg3.png");

    paddle = new Entity(window, "normal_paddle.png", 305, 490);

    ball = new Ball(window, "ball.png", window->getWidth() / 2, window->getHeight() / 2, paddle);

    currentLevel = 1;
    bricksLeft = 0;
    maxBricks = 0;
    totalBricksDestroyed = 0;

    powerupTimer = 9999;
    powerUpActive = false;

    std::string resPath = "res";
    std::string collidePath = "";
    collidePath = resPath + PATH_SEP + "hit.wav";
    ballHitSound = Mix_LoadWAV(collidePath.c_str());

    std::string brickBreakSoundPath = resPath + PATH_SEP + "brick.wav";
    brickBreakSound = Mix_LoadWAV(brickBreakSoundPath.c_str());

    showMessage = false;
    message = "";
}

void GameManager::initGame(bool fresh)
{
    paddle->setMoveRate(8);
    paddle->setTexture("normal_paddle.png");
    paddle->setX(305);
    paddle->setY(490);
    paddle->stopMoving(MOVE_LEFT);
    paddle->stopMoving(MOVE_RIGHT);

    ball->setOnPaddle(true);

    randNum = rand() % 5;
    randPos = rand() % (window->getWidth() / 2);
    mod = new Mods(window, "bonus.png", randPos, 0 );
    bonus_life = new Mods(window, "bonus_health.png", randPos, 0 );
    isPressed = false;

    powerUpActive = false;

    upNum = rand() % 2;
    downNum = rand() % 2;

    entities = std::vector<Entity*>();

    if (fresh)
    {
        currentLevel = 1;
        totalBricksDestroyed = 0;
        remainingLives = 3;
        ball->setLives(remainingLives);
    } 

    LevelLoader* loader = new LevelLoader(this);
    switch (currentLevel)
    {
        case 1:
            loader->openMap("lvl1.txt", maxBricks);

            break;
        case 2:
            loader->openMap("lvl2.txt", maxBricks);

            break;
        case 3:
            loader->openMap("lvl3.txt", maxBricks);

            break;
        case 4:
            loader->openMap("lvl4.txt", maxBricks);

            break;
        case 5:
            loader->openMap("lvl5.txt", maxBricks);

            break;
        default:
            currentState = STATE_WINNER;
            break;
    }

    if (currentState == STATE_PLAYING)
    {
        bricksLeft = maxBricks;
        levelOver = false;
    }
}

void GameManager::runGame()
{
    Menu mainMenu(this);
    mainMenu.addEntry(" Play ");
    mainMenu.addEntry(" Levels ");
    mainMenu.addEntry(" How to Play ");
    mainMenu.addEntry(" Creator ");
    mainMenu.addEntry(" Exit ");

    Timer fpsTimer;
    Timer capTimer;

    uint32_t frameCount = 0;
    fpsTimer.start();

    while (!_quit)
    {
        window->clear();

        capTimer.start();

        

        switch (currentState)
        {
        case STATE_MENU:
        {
            window->renderTexture(bgTexture, 0, 0);
            mainMenu.tick();
            break;
        }
        case STATE_LEVELS:
        {
            window->renderTexture(bgTexture, 0, 0);
            printLevels();
            listenForQuit();
            break;
        }
        case STATE_HOWTOPLAY:
        {
            window->renderTexture(bg2Texture, 0, 0);
            printHow();
            listenForQuit();
            break;
        }
        case STATE_CREDITS:
        {
            window->renderTexture(bg2Texture, 0, 0);
            printC();
            listenForQuit();
            break;
        }
        case STATE_PLAYING:
            window->renderTexture(bgGameTexture, 0, 0);
            gameTick();
            break;
        case STATE_WINNER:
        {
            window->renderTexture(bgTexture, 0, 0);
            window->renderCenteredText(" YOU WON ", 100, { 0, 0, 0 }, 75, FONT_RENDER_BLENDED, { 0, 0, 0 });
            window->renderCenteredText(" Final Score: " + std::to_string(calcScore()), 180, { 0, 0, 0 }, 75, FONT_RENDER_BLENDED, { 0, 0, 0 });
            listenForQuit();
            break;
        }

        default:
            break;
        }

        window->render();

        frameCount++;

        if (capTimer.getTicks() < (1000 / window->getMaxFps()))
        {
            int waitTime = (1000 / window->getMaxFps()) - capTimer.getTicks();
            SDL_Delay(waitTime);   
        }

            float avgFPS = frameCount / ( fpsTimer.getTicks() / 1000.f );
				if( avgFPS > 2000000 )
				{
					avgFPS = 0;
				}

            std::string title = "Break Braker | FPS: " + std::to_string((avgFPS));
            window->updateWindow(title.c_str());
            
    }
}

void GameManager::gameTick()
{
    bool repeatKey = SDL_PollEvent(&event) == 1;



    if (levelOver)
    {
        currentLevel++;
        initGame(false);
        levelOver = false;
        return;
    }

    if(ball->getLives() < 1)
    {
        
        window->renderCenteredText(" GAME OVER ", window->getHeight()/4, {0,0,0}, 50, FONT_RENDER_BLENDED, {255,255,255});
        window->renderCenteredText(" Score: " + std::to_string(calcScore()), window->getHeight()/2, {0,0,0}, 50, FONT_RENDER_BLENDED, {255,255,255});
        listenForQuit();
        return;
    }

    switch (event.type)
    {
    case SDL_QUIT:
        _quit = true;
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            paddle->startMoving(MOVE_LEFT);
            break;
        case SDLK_RIGHT:
            paddle->startMoving(MOVE_RIGHT);
            break;
        case SDLK_SPACE:
            if (ball->isOnPaddle())
                ball->detach();
            isPressed = true;
            break;
        case SDLK_ESCAPE:
            if (repeatKey)
            {
                setState(STATE_MENU);
                return;
            }
        }
        break;

    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            paddle->stopMoving(MOVE_LEFT);
            break;
        case SDLK_RIGHT:
            paddle->stopMoving(MOVE_RIGHT);
            break;
        }
        break;
    }

	bool collidedThisTick = false;
    for (Entity* e : entities)
    {
        bool playedSound = false;
        if (e->isActive())
        {
            if ((ball->collidedWith(e)) && (e->isActive()) && !collidedThisTick)
            {
                collidedThisTick = true;
                ball->handleCollision(e);
                if (e->getTypeId() == TYPEID_BRICK)
                {
                    if (!((Brick*)e)->dealDamage(1))
                    {
                        bricksLeft--;
                        totalBricksDestroyed=totalBricksDestroyed+(currentLevel);
                        Mix_PlayChannel(-1, brickBreakSound, 0);
                        playedSound = true;
                    }
                }

                if (!playedSound)
                    Mix_PlayChannel(-1, ballHitSound, 0);
            }
            e->update();
        }
    }

    /*PowerUPs*/

    powerupTimer++;
    
    if(randNum == 0 && isPressed == true && !powerUpActive)
    {
        mod->update();
        if(mod->collidedWith(paddle))
        {
            powerupTimer = 0;
            paddle->setMoveRate(10);
            mod->remove();
            powerUpActive = true;
        }
    }

    if(randNum == 1 && isPressed == true && !powerUpActive)
    {
        mod->update();
        if(mod->collidedWith(paddle))
        {
            powerupTimer = 0;
            paddle->setMoveRate(6);
            mod->remove();
            powerUpActive = true;
        }
    }

    if(randNum == 2 && isPressed == true && !powerUpActive)
    {
        mod->update();
        if(mod->collidedWith(paddle))
        {
            powerupTimer = 0;
            paddle->setTexture("big_paddle.png");
            mod->remove();
            powerUpActive = true;
        }
    }

    if(randNum == 3 && isPressed == true && !powerUpActive)
    {
        mod->update();
        if(mod->collidedWith(paddle))
        {
            powerupTimer = 0;
            paddle->setTexture("small_paddle.png");
            mod->remove();
            powerUpActive = true;
        }
    }

        if(randNum == 4 && isPressed == true && !powerUpActive)
    {
        bonus_life->update();
        if(bonus_life->collidedWith(paddle))
        {
            powerupTimer = 0;
            ball->setLives(ball->getLives()+1);
            bonus_life->remove();
            powerUpActive = true;
        }
    }

    uint8_t c = powerupTimer;
    if (randNum == 0 && powerupTimer < 254)
    {
        window->renderCenteredText("Faster Paddle!", 300, { c,c,c }, 30, FONT_RENDER_BLENDED, { 100,100,100 });
    }
    if (randNum == 1 && powerupTimer < 254)
    {
        window->renderCenteredText("Slower Paddle!", 300, { c,c,c }, 30, FONT_RENDER_BLENDED, { 100,100,100 });
    }
    if (randNum == 2 && powerupTimer < 254)
    {
        window->renderCenteredText("Bigger Paddle!", 300, { c,c,c }, 30, FONT_RENDER_BLENDED, { 100,100,100 });
    }
    if (randNum == 3 && powerupTimer < 254)
    {
        window->renderCenteredText("Smaller Paddle!", 300, { c,c,c }, 30, FONT_RENDER_BLENDED, { 100,100,100 });
    }
    if (randNum == 4 && powerupTimer < 254)
    {
        window->renderCenteredText("Bonus Life!", 300, { c,c,c }, 30, FONT_RENDER_BLENDED, { 100,100,100 });
    }

    /*EndPowerUPs*/

    if (ball->collidedWith(paddle))
    {
        Mix_PlayChannel(-1, ballHitSound, 0);
        ball->handleCollision(paddle);
    }
    paddle->update();

    ball->update();
    window->renderText("Lives: " + std::to_string(ball->getLives()), 5, 0, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });
    window->renderText("Score: " + std::to_string(calcScore()), 5, 30, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });
    window->renderText("Level: " + std::to_string(currentLevel), 5, 445, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });

    if (bricksLeft == 0)
    {
        levelOver = true;
    }
}

void GameManager::addEntity(Entity* e)
{
	entities.push_back(e);
}

void GameManager::setState(int state)
{
    currentState = state;
}

void GameManager::printLevels()
{
    window->renderCenteredText(" Level 1 ", 100, { 0, 0, 0 }, 45, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" Level 2 ", 175, { 0, 0, 0 }, 45, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" Level 3 ", 250, { 0, 0, 0 }, 45, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" Level 4 ", 325, { 0, 0, 0 }, 45, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" Level 5 ", 400, { 0, 0, 0 }, 45, FONT_RENDER_SHADED, {240, 240, 240});
}

void GameManager::printC()
{
    window->renderCenteredText(" Aleksander Bober ", 100-40, { 0, 0, 0 }, 45, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" s18855 ", 175-40, { 0, 0, 0 }, 45, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" ----- ", 250-40, { 0, 0, 0 }, 45, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" SGD ", 325-40, { 0, 0, 0 }, 45, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" 2021 ", 400-40, { 0, 0, 0 }, 45, FONT_RENDER_SHADED, {240, 240, 240});
}

void GameManager::printHow()
{
    window->renderCenteredText(" Move Paddle With Arrows '<' and '>' ", 50, { 0, 0, 0 }, 25, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" Launch Ball with 'Space' ", 100, { 0, 0, 0 }, 25, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" ----- ", 150, { 0, 0, 0 }, 25, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" On the begginig of level 'Power Up' will spawn ", 200, { 0, 0, 0 }, 25, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" It can make paddle : ", 250, { 0, 0, 0 }, 25, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" Slower Faster Smaller or Bigger ", 300, { 0, 0, 0 }, 25, FONT_RENDER_SHADED, {240, 240, 240});
    window->renderCenteredText(" U can also get 'Bonus Life' ", 350, { 0, 0, 0 }, 25, FONT_RENDER_SHADED, {240, 240, 240});
}

void GameManager::listenForQuit()
{
    SDL_Event currEvent;
    bool repeatKey = SDL_PollEvent(&currEvent) == 1;
    
    switch (currEvent.type)
    {
    case SDL_QUIT:
        _quit = true;
        return;
    case SDL_KEYDOWN:
        if (repeatKey)
        {
            switch (currEvent.key.keysym.sym)
            {
            case SDLK_SPACE:
            case SDLK_RETURN:
            case SDLK_ESCAPE:
                setState(STATE_MENU);
            }
        }
    }
}

int GameManager::calcScore()
{
    return  (totalBricksDestroyed);
}

int GameManager::saveLife()
{
    return  (ball->getLives());
}

