#include <iostream>
#include <string>
#include "Entity.h"
#include "Window.h"

Entity::Entity(Window* window, const std::string& textureName, int xPos, int yPos):
    textureName(textureName)
{
    this->window = window;
    this->xPos = xPos;
    this->yPos = yPos;

    this->typeId = TYPEID_ENTITY;

    this->texture = window->loadTexture(textureName);

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    moveState = MOVE_NONE;
    moveRate = 1;

    active = true;
}

Entity::~Entity()
{
    SDL_DestroyTexture(texture);
}

void Entity::update()
{
    if (!isActive())
        return;

    if (isMoving(MOVE_UP))
        yPos -= moveRate;

    if (isMoving(MOVE_DOWN))
        yPos += moveRate;

    if (isMoving(MOVE_LEFT))
        xPos -= moveRate;

    if (isMoving(MOVE_RIGHT))
        xPos += moveRate;

    if (xPos < 0)
        xPos = 0;

    if (yPos < 0)
        yPos = 0;

    if (xPos > window->getWidth() - width)
        xPos = window->getWidth() - width;

    if (yPos > window->getHeight() - height)
        yPos = window->getHeight() - height;

    window->renderTexture(texture, xPos, yPos);
}

bool Entity::collidedWith(Entity* entity)
{
    if (!entity)
        return false;

    if (this == entity)
        return false;
    
    if (!entity->isActive())
        return false;

    SDL_Rect rect;
    rect.x = xPos;
    rect.y = yPos;
    rect.h = height;
    rect.w = width;

    SDL_Rect rectCol;
    rectCol.x = entity->getX();
    rectCol.y = entity->getY();
    rectCol.h = entity->getHeight();
    rectCol.w = entity->getWidth();

    return SDL_HasIntersection(&rect, &rectCol) != 0;
}

void Entity::remove()
{
    if (!texture)
    {
        return;
    }

    SDL_DestroyTexture(texture);
    active = false;
}

void Entity::setTexture(const std::string& textureName)
{
    const std::string old = this->textureName;
    this->texture = window->loadTexture(textureName);

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Entity::startMoving(int direction)
{
    moveState |= direction;
}

void Entity::stopMoving(int direction)
{
    moveState &= ~direction;
}

bool Entity::isMoving(int direction)
{
    return (moveState & direction) != 0;
}

bool operator==(const Entity& left, const Entity& right)
{
    return (left.xPos == right.xPos)
        && (left.yPos == right.yPos)
        && (left.textureName == right.textureName);
}
