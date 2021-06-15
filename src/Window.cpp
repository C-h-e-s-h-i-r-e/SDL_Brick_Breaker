#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "Window.h"

Window::Window(const std::string& title, int width, int height, int fps)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    if (TTF_Init() == -1)
    {
            exit(1);
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    this->width = width;
    this->height = height;
    this->maxFps = fps;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

    std::string resPath = "res";
    std::string filePath = "";
    filePath = resPath + PATH_SEP + "bmusic.wav";

    music = Mix_LoadMUS(filePath.c_str());

    if (!music)
        printf("Mix_LoadMUS(\"bmusic.wav\"): %s\n", Mix_GetError());

    Mix_PlayMusic( music, -1 );

}

void Window::updateWindow(std::string newTitle ){
    SDL_SetWindowTitle(window,newTitle.c_str());
}

void Window::cleanupAndExit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

static std::string buildSDLError(const std::string& err)
{
    std::ostringstream stream;
    stream << err << SDL_GetError();
    return stream.str();
}

SDL_Texture* Window::loadTexture(const std::string& fileName)
{
    std::string resPath = "res";
    std::string filePath = "";
    filePath = resPath + PATH_SEP + fileName;
    
    SDL_Texture* texture = NULL;

    SDL_Surface* img = IMG_Load(filePath.c_str());

    if (!img)
    {
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    if (!texture)
    {
               return NULL;
    }

    return texture;
}

void Window::renderTexture(SDL_Texture* texture, int xPos, int yPos)
{
    SDL_Rect destination;
    destination.x = xPos;
    destination.y = yPos;

    SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);

    SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void Window::renderText(const std::string& msg, int xPos, int yPos, SDL_Color color, int size, int renderType, SDL_Color bgColor = {0, 0, 0})
{   
    std::string resPath = "res";
    std::string filePath = "";
    filePath = resPath + PATH_SEP + FONT_NAME;

    TTF_Font* font = TTF_OpenFont(filePath.c_str(), size);
    if (!font)
    {
        return;
    }

    SDL_Surface* msgSurface = nullptr;

    switch (renderType)
    {
    case FONT_RENDER_SOLID:
        msgSurface = TTF_RenderText_Solid(font, msg.c_str(), color);
        break;
    case FONT_RENDER_BLENDED:
        msgSurface = TTF_RenderText_Blended(font, msg.c_str(), color);
        break;
    case FONT_RENDER_SHADED:
        msgSurface = TTF_RenderText_Shaded(font, msg.c_str(), color, bgColor);
        break;
    default:
        msgSurface = TTF_RenderText_Solid(font, msg.c_str(), color);
        break;
    }

    SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(renderer, msgSurface);
    SDL_FreeSurface(msgSurface);

    SDL_Rect rect;
    rect.x = xPos;
    rect.y = yPos;
    SDL_QueryTexture(msgTexture, NULL, NULL, &rect.w, &rect.h);

    SDL_RenderCopy(renderer, msgTexture, NULL, &rect);

    SDL_DestroyTexture(msgTexture);
    TTF_CloseFont(font);
}

void Window::renderCenteredText(const std::string& msg, int yPos, SDL_Color color, int size, int renderType, SDL_Color bgColor = {0, 0, 0})
{
    std::string resPath = "res";
    std::string filePath = "";
    filePath = resPath + PATH_SEP + FONT_NAME;

    TTF_Font* font = TTF_OpenFont(filePath.c_str(), size);
    if (!font)
    {
        return;
    }

    SDL_Surface* msgSurface = nullptr;

    switch (renderType)
    {
    case FONT_RENDER_SOLID:
        msgSurface = TTF_RenderText_Solid(font, msg.c_str(), color);
        break;
    case FONT_RENDER_BLENDED:
        msgSurface = TTF_RenderText_Blended(font, msg.c_str(), color);
        break;
    case FONT_RENDER_SHADED:
        msgSurface = TTF_RenderText_Shaded(font, msg.c_str(), color, bgColor);
        break;
    default:
        msgSurface = TTF_RenderText_Solid(font, msg.c_str(), color);
        break;
    }

    SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(renderer, msgSurface);
    SDL_FreeSurface(msgSurface);

    SDL_Rect rect;
    rect.y = yPos;
    SDL_QueryTexture(msgTexture, NULL, NULL, &rect.w, &rect.h);

    rect.x = (getWidth() - rect.w) / 2;

    SDL_RenderCopy(renderer, msgTexture, NULL, &rect);

    SDL_DestroyTexture(msgTexture);
    TTF_CloseFont(font);
}
