#include "Menu.h"
#include "Window.h"

Menu::Menu(GameManager* mgr) :
manager(mgr)
{
    activeIndex = 0;
}

void Menu::tick()
{    
    SDL_Event currEvent;
    bool repeatKey = SDL_PollEvent(&currEvent) == 1;
    
    switch (currEvent.type)
    {
    case SDL_QUIT:
        manager->quit();
        return;
    case SDL_KEYDOWN:
        if (repeatKey)
        {
            switch (currEvent.key.keysym.sym)
            {
            case SDLK_SPACE:
            case SDLK_RETURN:
                switch (activeIndex)
                {
                case 0:
                    manager->setState(STATE_PLAYING);
                    manager->initGame(true);
                    return;
                case 1:
                    manager->setState(STATE_VOLUME);
                    break;
                case 2:
                    manager->setState(STATE_HOWTOPLAY);
                    break;
                case 3:
                    manager->setState(STATE_CREDITS);
                    break;
                case 4:
                    manager->quit();
                    return;
                }
                break;
            case SDLK_UP:
                activeIndex--;
                if (activeIndex < 0)
                    activeIndex = menuEntries.size() - 1;
                break;
            case SDLK_DOWN:
                activeIndex++;
                if (activeIndex > menuEntries.size() - 1)
                    activeIndex = 0;
                break;

            }
        }
        break;
    }

    int yPos = 1;
    for (int i = 0; i < menuEntries.size(); i++)
    {
        if (i == activeIndex)
            manager->getWindow()->renderCenteredText(menuEntries[i], yPos, { 250, 250, 240 }, 60, FONT_RENDER_SHADED, {0, 0, 0});
        else
            manager->getWindow()->renderCenteredText(menuEntries[i], yPos, { 0, 0, 0 }, 50, FONT_RENDER_BLENDED, {0, 0, 0});
        yPos += 100;
    }
}

void Menu::addEntry(const std::string& text)
{
    menuEntries.push_back(text);
}
