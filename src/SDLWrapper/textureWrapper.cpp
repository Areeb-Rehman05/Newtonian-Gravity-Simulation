#include <SDLWrapper/textureWrapper.h>

Texture::Texture() {
    //Intitialize
    texture = NULL;
    height = 0;
    width = 0;
}

Texture::~Texture() {
    //Free textures
    free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer *renderer) {
    //Free previous texture
    free();

    SDL_Texture* newTexture = NULL;

    //load image at the path
    SDL_Surface* newImage = IMG_Load(path.c_str());
    if(newImage == NULL) {
        printf("Failed to load image %s ! SDLImage_Error: %s", path, IMG_GetError());
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, newImage);
        if(newTexture == NULL) {
            printf("Unable to create texture from surface! SDL_Error: %s", SDL_GetError());
        } else {
            //Get image dimensions
            height = newImage->h;
            width = newImage->w;
        }

        //Free the old surface
        SDL_FreeSurface(newImage);
    }

    //Return success and assigne new texture variable
    texture = newTexture;
    return texture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer *renderer) {
    //Free previous texture
    free();

    //Render the text surface from font
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, textureText.c_str(), textColor);
    if(textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(texture == NULL) {
            printf("Unable to create texture from rendererd text! SDL_Error: %s\n", SDL_GetError());
        } else {
            width = textSurface->w;
            height = textSurface->h;
        }

        //Remove the old surface
        SDL_FreeSurface(textSurface);
    }

    return texture != NULL;
}

bool Texture::setFont(std::string path, int fontSize) {
    font = TTF_OpenFont(path.c_str(), fontSize);
    if(font == NULL) {
        printf("font at %s could not be loaded! TTF_Error: %s", path, TTF_GetError());
        return false;
    }

    return true;
}

void Texture::free() {
    if(texture != NULL) {
        SDL_DestroyTexture(texture);
        width = 0;
        height = 0;
    }
}

void Texture::render(int x, int y, SDL_Renderer *renderer) {
    //Set rendering space and render to the screen
    SDL_Rect renderQuad = {x,y,width,height};

    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}