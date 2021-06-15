#include "Mods.h"

Mods::Mods(Window* window, const std::string& textureName, int xPos, int yPos) :
    Entity(window, textureName, xPos, yPos)
{
	yVelocity = 5;
	xVelocity = 0;
}

void Mods::update()
{
    if (!isActive())
        return;
    
    xPos += xVelocity;
    yPos += yVelocity;
	window->renderTexture(texture, xPos, yPos);
}
