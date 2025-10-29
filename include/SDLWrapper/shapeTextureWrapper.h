#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

class shapeTexture {
    public:
        //Initialize Variables
        shapeTexture();

        //Deallocate memory
        ~shapeTexture();

        //Set dimensions of the shape
        void setDimensions(int x, int y, int w, int h);

        //Set color of the shape;
        void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        //Check for if the mouse is on the shape
        bool isHovering();

        //Renders shape at a given point
        void render (SDL_Renderer *renderer);

        //Get Rect
        SDL_Rect getRect();

        //Free up memory 
        void free();

    private:
        //Dimensions of the Rect
        SDL_Rect shapeRect;

        //Color of the Rect
        SDL_Color shapeColor;
};