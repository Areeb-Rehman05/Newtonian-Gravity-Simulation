#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>
#include <vector>
#include <utility>

using Point = std::pair<int,int>;

extern std::vector<SDL_Color> colors;

class SDLWrapper {
    protected:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        TTF_Font* font;
    public:
        SDLWrapper();
        ~SDLWrapper();

        void constructApp();

        void createTextLabel(const std::string& text, int x, int y, int w, int h);

        void createTextBox(int x, int y, int w, int h);

        void listenForInput();

        void mapPoints(const std::vector<std::vector<Point>>& points_array);
};