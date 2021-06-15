#include <cmath>

#include "Ball.h"
#include "Brick.h"

Ball::Ball(Window* window, const std::string& textureName, int xPos, int yPos, Entity* linkedPaddle) :
    Entity(window, textureName, xPos, yPos)
{
    this->typeId = TYPEID_BALL;
    this->linkedPaddle = linkedPaddle;
    lives = 3;
    y = 0;
    x = 0;
}

void Ball::update()
{

    if (lives <= 0)
        return;

    if (onPaddle)
    {
        xPos = linkedPaddle->getX() + (linkedPaddle->getWidth()/2) - getWidth()/2;
        yPos = linkedPaddle->getY() - getHeight();
        window->renderTexture(texture, xPos, yPos);
        return;
    }

    xPos += x;
    yPos += y;

    if (xPos < 0)
    {
        xPos = 0;
        x = -x;
    }

	if(xPos > window->getWidth() - getWidth())
	{
		xPos = window->getWidth() - getWidth();
		x = -x;
	}

    if (yPos < 0)
    {
        yPos = 0;
        y = -y;
    }

    if (yPos > window->getHeight() - height)
    {
        lives--;
        setOnPaddle(true);
    }

    window->renderTexture(texture, xPos, yPos);
}

void Ball::handleCollision(Entity* entity)
{
    if (!entity->isActive())
        return;

	double totalSpeed = sqrt(x*x + y*y);

    double ballCenter = xPos + (width / 2);
    double entityCenter = entity->getX() + (entity->getWidth() / 2);

	if (entity->getTypeId() == TYPEID_BRICK)
	{
		double checkRight = std::abs(entity->getX() - (xPos + width));
		double checkLeft = std::abs((entity->getX() + entity->getWidth()) - xPos );
		double checkHorizontal;
		if (checkLeft < checkRight)
		{
			checkHorizontal = checkLeft;
		}
		else
		{
			checkHorizontal = checkRight;
		}

		double checkUp = std::abs((entity->getY() + entity->getHeight()) - yPos);
		double checkDown = std::abs(entity->getY() - (yPos + height));
		double checkVertical;
		if (checkUp < checkDown)
		{
			checkVertical = checkUp;
		}
		else
		{
			checkVertical = checkDown;
		}

		if (checkHorizontal > checkVertical)
			y = -y;
		else if (std::abs(checkHorizontal - checkVertical)<1.2)
		{
			y = -y;
			x = -x;
		}
		else
			x = -x;

	}

	else
	{
		double horizontalDifference = ballCenter - entityCenter;
		totalSpeed += 1;
		if (totalSpeed > 10)
			totalSpeed = 10;
		double w = entity->getWidth()/2.0;
		double angle = horizontalDifference / w;
		x = angle*totalSpeed*.8;
		y = 0 - sqrt(totalSpeed*totalSpeed - x*x);
		if (std::abs(y) < .8)
			y = -1;
	}
}

void Ball::setOnPaddle(bool apply)
{
    onPaddle = apply;
}

void Ball::setLives(int count)
{
    lives = count;
}

void Ball::detach()
{
    onPaddle = false;

    x = linkedPaddle->isMoving(MOVE_LEFT) ? -5 : 5;
    y = -5;
}
