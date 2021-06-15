#ifndef _LEVEL_LOADER_H
#define _LEVEL_LOADER_H

#include <vector>
#include "Window.h"
#include "Entity.h"
#include "Ball.h"
#include "Mods.h"
#include "GameManager.h"
#include <iostream>
#include <vector>

class LevelLoader
{
    public:

		LevelLoader(GameManager* gm);
        void openMap(const std::string& mapName, int& maxBlocks);

    private:
		GameManager* gameManager;
};

#endif
