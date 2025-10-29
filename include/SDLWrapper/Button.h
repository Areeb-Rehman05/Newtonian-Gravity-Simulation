#pragma once

#include <SDLWrapper/shapeTextureWrapper.h>
#include <SDLWrapper/textureWrapper.h>


//Uses a shapeTextureWrapper object to create a textbox to listen for events 
class Button {
    public:
        //Initialize Variables
        Button();

        //Deallocate memory
        ~Button();

        //Create text box
        void createButton(int x, int y, int w, int h, SDL_Color boxColor);

        //Set font and color for the textbox
        void setFont(std::string fontPath, int fontSize, SDL_Color textColor);

        //Add the text to the button
        void setText(std::string buttonText, SDL_Renderer* renderer);

        //Handle the text inputs
        bool handleClick(SDL_Renderer* renderer, SDL_Event& event);

        //Deallocates the texture
        void free();

        //Renders textBox at a given point
        void render (SDL_Renderer *renderer);

    private:
        //The shapeTexture
        shapeTexture box;

        //The texture for the text inside the Button
        Texture text;

        //The color of the text
        SDL_Color textColor;
};