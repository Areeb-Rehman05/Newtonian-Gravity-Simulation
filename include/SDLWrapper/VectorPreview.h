#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <Simulations/Body.h>
#include <algorithm>

class VectorPreview {
    public:
        VectorPreview();
        ~VectorPreview();

        void init(int x, int y, int w, int h);
        void updateData(const std::vector<Body> bodies);
        void render(SDL_Renderer* renderer);
        void free();

        int getScale();

    private:
        //Just some colors that have a high contrast with black
        SDL_Color bodyColors[7] = {
            {255, 255, 0, 255},
            {0, 255, 0, 255},
            {0, 255, 255, 255},
            {255, 0, 255},
            {255, 0, 0},
            {255, 165, 0},
            {0, 0, 255}
        };
        
        SDL_Rect previewRect;
        std::vector<Body> bodyData;

        double scale;
};