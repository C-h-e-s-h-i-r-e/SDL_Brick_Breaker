#ifndef _MENU_H
#define _MENU_H

#include <vector>
#include "GameManager.h"

class Menu
{
    public:
        Menu(GameManager* mgr);
        void tick();
        void addEntry(const std::string& text);

    private:
        std::vector<std::string> menuEntries;
        GameManager* manager;

        int activeIndex;
};

#endif