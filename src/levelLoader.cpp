#include <iostream>
#include <fstream>
#include <string>
#include "levelLoader.h"
#include "Brick.h"

using namespace std;

LevelLoader::LevelLoader(GameManager* gm)
{
	gameManager = gm;
}

#define BLOCK_WIDTH 90

void LevelLoader::openMap(const std::string& mapName, int& maxBlocks)
{
    string line;
	ifstream myFile(mapName);

    if (!myFile.is_open())
    {
        maxBlocks = 0;
    }

    int blockCount = 0;

	int ypos = 30;
	while (getline(myFile, line))
	{
		int xpos = 25;
		while (line.size() > 0)
		{
			char hp = line.at(0);
			int health = hp - '0';

			if (health > 0)
			{
				if (health == 6)
					gameManager->addEntity(new Brick(gameManager->getWindow(), "hp6.png", xpos, ypos, health));
				if (health == 5)
					gameManager->addEntity(new Brick(gameManager->getWindow(), "hp5.png", xpos, ypos, health));
				if (health == 4)
					gameManager->addEntity(new Brick(gameManager->getWindow(), "hp4.png", xpos, ypos, health));
				if (health == 3)
					gameManager->addEntity(new Brick(gameManager->getWindow(), "hp3.png", xpos, ypos, health));
				if (health == 2)
					gameManager->addEntity(new Brick(gameManager->getWindow(), "hp2.png", xpos, ypos, health));
				if (health == 1)
					gameManager->addEntity(new Brick(gameManager->getWindow(), "hp1.png", xpos, ypos, health));

                blockCount++;
			}

			line.erase(0, 1);
			xpos += 100;

            if (xpos > gameManager->getWindow()->getWidth() - BLOCK_WIDTH)
                break;
		}
		ypos += 30;

        if (ypos > gameManager->getWindow()->getHeight())
            break;
	}

	myFile.close();
    maxBlocks = blockCount;
	return;
}
