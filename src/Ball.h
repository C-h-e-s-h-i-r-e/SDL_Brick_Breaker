#ifndef _BALL_H
#define _BALL_H

#include <iostream>
#include "Entity.h"

class Ball : public Entity
{
public:
    Ball(Window* window, const std::string& textureName, int xPos, int yPos, Entity* linkedPaddle);

    virtual void update();

    void handleCollision(Entity* entity);

    void setOnPaddle(bool apply);

    bool isOnPaddle() { return onPaddle; }

    void detach();

    void setLives(int count);
    int getLives() { return lives; }

private:
    int x;
    int y;

    Entity* linkedPaddle;
    bool onPaddle;

    int lives;
};
#endif
