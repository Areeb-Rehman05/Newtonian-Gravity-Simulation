#include <SDLWrapper/shapeTextureWrapper.h>

shapeTexture::shapeTexture() {
    shapeRect = {};

    shapeColor = {};
}

shapeTexture::~shapeTexture() {
    free();
}

void shapeTexture::setDimensions(int x, int y, int w, int h) {
    shapeRect = {x, y, w, h};
}

void shapeTexture::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    shapeColor = {r, g, b, a};
}

bool shapeTexture::isHovering() {
    int x,y;
    SDL_GetMouseState(&x, &y);

    //Check if the x and y is within the bounds of the textbox
    bool isHovering = (x >= shapeRect.x && x <= shapeRect.x + shapeRect.w &&
                         y >= shapeRect.y && y <= shapeRect.y + shapeRect.h);

    return isHovering;
}

void shapeTexture::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, shapeColor.r, shapeColor.g, shapeColor.b, shapeColor.a);
    SDL_RenderFillRect(renderer, &shapeRect);
}

SDL_Rect shapeTexture::getRect() {
    return shapeRect;
}

void shapeTexture::free() {
    shapeRect = {0, 0, 0, 0};

    shapeColor = {0, 0, 0, 255};
}