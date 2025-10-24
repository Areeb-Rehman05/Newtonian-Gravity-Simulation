#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDLWrapper/Screen.h>
#include <Simulations/Body.h>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>

using Point = std::pair<int,int>;

enum class ScreenID {Menu, Running};

class Screen;

class SDLWrapper {
    public:
        SDLWrapper();
        ~SDLWrapper();

        void init(std::string title, int width, int height);
        void changeState(ScreenID newScreen);
        
        void handleEvents();
        void update();
        void render();

        SDL_Renderer* getRenderer();
        int getScreenWidth();
        int getScreenHeight();

        bool running();
        void clean();

    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
        Screen* currentScreen;

        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
};