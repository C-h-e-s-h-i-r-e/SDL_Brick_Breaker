#ifndef _MODS_H
#define _MODS_H

#include "Entity.h"
#include <iostream>

class Mods : public Entity
{
    public:
        Mods(Window* window, const std::string& textureName, int xPos, int yPos);

        
        virtual void update();

    private:
        int xVelocity;
        int yVelocity;
};

#endif
