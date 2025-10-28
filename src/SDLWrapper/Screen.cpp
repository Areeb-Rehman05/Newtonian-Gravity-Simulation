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

    sunTextBox.setDimensions(250, 50, 150, 30);
}

void menuScreen::handleEvents(SDLWrapper* sdl, SDL_Event& event) {
    if (sunTextBox.isHovering()) {
        sunTextBox.setColor(128, 128, 128, 255);

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                textLine.setDimensions(251, 49, 1, 40);
                textLine.setColor(0, 0, 0, 255);
            }
        }
    } else {
        sunTextBox.setColor(255, 255, 255, 255);
    }
}

void menuScreen::update(SDLWrapper* sdl) {

}

void menuScreen::render(SDLWrapper* sdl) {
    sunMass.render(100, 50, sdl->getRenderer());

    sunTextBox.render(sdl->getRenderer());
    textLine.render(sdl->getRenderer());
}

void menuScreen::clean() {

}