#pragma once

#include <SDL2/SDL.h>
#include <SDLWrapper/Screen.h>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>

using Point = std::pair<int,int>;

struct simulationData {
    std::string sunMass = "";
    int bodyNums = 1; 
};

enum class ScreenID {Menu, Running};

class Screen;

class SDLWrapper {
    public:
        simulationData data;

        SDLWrapper();
        ~SDLWrapper();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void changeState(ScreenID newScreen);
        
        void handleEvents();
        void update();
        void render();

        SDL_Renderer* getRenderer();
        bool running();
        void clean();

    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
        std::unique_ptr<Screen> currentState;
};