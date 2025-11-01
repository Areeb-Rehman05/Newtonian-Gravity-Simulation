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

struct userData {
    int totalBodies;
    int sunMass;
    std::vector<Body> bodies;
};

enum class ScreenID {Menu, Bodies, Running};

class Screen;

class SDLWrapper {
    public:
        userData sharedData;

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