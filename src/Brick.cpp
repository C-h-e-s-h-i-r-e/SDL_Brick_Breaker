#include "Brick.h"

Brick::Brick(Window* window, const std::string& textureName, int xPos, int yPos, int maxHealth) :
Entity(window, textureName, xPos, yPos)
{
    this->typeId = TYPEID_BRICK;

	this->maxHealth = maxHealth;
    health = maxHealth;
}

bool Brick::dealDamage(int dmg)
{



    health -= dmg;

    if (health == 5)
		setTexture("hp5.png");
    if (health == 4)
		setTexture("hp4.png");
    if (health == 3)
		setTexture("hp3.png");
	if (health == 2)
		setTexture("hp2.png");
	if (health == 1)
		setTexture("hp1.png");

    if (health <= 0)
    {
        remove();
        return false;
    }

    return true;
}
