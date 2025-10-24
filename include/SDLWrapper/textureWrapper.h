//Texture wrapper class that is inspired by Lazy Foo's SDL2 tutorial
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture {
    public:
        //Initialize Variables
        Texture();

        //Deallocate memory
        ~Texture();

        //Load media from at the specified path and assign it to a renderer
        bool loadFromFile(std::string path, SDL_Renderer *renderer);

        //Creates image from font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer *renderer);

        //Set font of the texture(This is to be used prior to the loadFromRenderedText function)
        bool setFont(std::string path, int fontSize);

        //Deallocates the texture
        void free();

        //Renders texture at a given point
        void render (int x, int y, SDL_Renderer *renderer);

        //Get Texture dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual texture
        SDL_Texture* texture;

        //Image dimensions
        int height;
        int width;

        //Font path
        TTF_Font* font = NULL;
};