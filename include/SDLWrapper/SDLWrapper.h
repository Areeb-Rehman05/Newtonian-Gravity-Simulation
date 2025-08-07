#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_FontCache/SDL_FontCache.h>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>

using Point = std::pair<int,int>;

extern std::vector<SDL_Color> colors;

class SDLWrapper {
    public:
        SDLWrapper();
        ~SDLWrapper();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        
        void handleEvents();
        void update();
        void render();
        void clean();

        bool running();

    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
        FC_Font* font;
        std::string sunMass = "";
        int stage;
        int bodyNums = 1; 
};