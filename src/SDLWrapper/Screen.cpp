#include <SDLWrapper/Screen.h>

Screen::Screen() {

}

Screen::~Screen() {}

// ------------- Menu Screen ------------
menuScreen::~menuScreen() {

}

void menuScreen::init(SDLWrapper* sdl) {
    SDL_Color textColor = {255, 255, 255};
    sunMass.setFont("/home/areeb-linux/codingProjects/Newtonian-Gravity-Simulation/fonts/ARIAL.TTF", 28);
    sunMass.loadFromRenderedText("Sun Mass: ", textColor, sdl->getRenderer());
}

void menuScreen::handleEvents(SDLWrapper* sdl, SDL_Event& event) {
    
}

void menuScreen::update(SDLWrapper* sdl) {

}

void menuScreen::render(SDLWrapper* sdl) {
    sunMass.render(100, 50, sdl->getRenderer());

    SDL_Rect fillRect = {250, 50, 150, 30};
    SDL_SetRenderDrawColor(sdl->getRenderer(), 255, 255, 255, 255);
    SDL_RenderFillRect(sdl->getRenderer(), &fillRect);
}

void menuScreen::clean() {

}