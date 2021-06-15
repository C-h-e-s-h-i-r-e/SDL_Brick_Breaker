#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <string>

#ifdef _WIN32
const char PATH_SEP = '\\';
#else
const char PATH_SEP = '/';
#endif

#define FONT_NAME "KarmaFuture.ttf"
#define FONT_STROKE_SIZE 2

enum FontRenderTypes
{
    FONT_RENDER_SOLID = 0,

    FONT_RENDER_BLENDED = 1,

    FONT_RENDER_SHADED = 2
};

class Window
{
    public:
        Window(const std::string& title, int width, int height, int fps);

        void cleanupAndExit();

        SDL_Texture* loadTexture(const std::string &file);

        void renderTexture(SDL_Texture* texture, int xPos, int yPos);

        void renderText(const std::string& msg, int xPos, int yPos, SDL_Color color, int size, int renderType, SDL_Color stroke);

        void renderCenteredText(const std::string& msg, int yPos, SDL_Color color, int size, int renderType, SDL_Color stroke);

        void updateWindow(std::string newTitle );

        void clear() { SDL_RenderClear(renderer); }

        void render() { SDL_RenderPresent(renderer); }

        int getWidth() { return width; }
        int getHeight() { return height; }
        int getMaxFps() { return maxFps; }
        

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        int width;
        int height;
        int maxFps;

};

#endif