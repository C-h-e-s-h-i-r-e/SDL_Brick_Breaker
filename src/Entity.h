#ifndef _ENTITY_H
#define _ENTITY_H

#include <SDL2/SDL.h>
#include "Window.h"

enum EntityMoveState
{
    MOVE_NONE =  0x00,
    MOVE_UP =    0x01,
    MOVE_DOWN =  0x02,
    MOVE_LEFT =  0x04,
    MOVE_RIGHT = 0x08,
    MOVE_ALL =   0x10
};

enum TypeIDs
{
    TYPEID_ENTITY = 0,
    TYPEID_BALL   = 1,
    TYPEID_BRICK  = 2,
    TYPEID_MOD    = 3
};

class Entity
{
    public:
        Entity(Window* window, const std::string& textureName, int xPos, int yPos);
        ~Entity();

        SDL_Texture* getTexture() { return texture; }
        int getX() { return xPos; }
        int getY() { return yPos; }
        int getMoveRate() { return moveRate; }
        int getHeight() { return height; }
        int getWidth() { return width; }
        int getTypeId() { return typeId; }

        void setTexture(const std::string& textureName);

        void setX(int x) { xPos = x; }
        void setY(int y) { yPos = y; }

        bool isMoving(int direction);

        bool isActive() { return active; }

        void setMoveRate(int rate) { moveRate = rate; }

        void startMoving(int direction);

        void stopMoving(int direction);

        virtual void update();

        void remove();

        bool collidedWith(Entity* entity);

        friend bool operator==(const Entity& left, const Entity& right);
        friend bool operator!=(const Entity& left, const Entity& right) { return !(left == right); }

    protected:
        Window* window;
        SDL_Texture* texture = NULL;
        const std::string textureName;

        int xPos;
        int yPos;

        int width;
        int height;

        int typeId;

        unsigned int moveState = MOVE_NONE;
        int moveRate = 0;

        bool active;
};

#endif
