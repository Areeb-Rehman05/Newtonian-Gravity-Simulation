#include <SDLWrapper/Screen.h>
#include <SDLWrapper/TextBox.h>

Screen::Screen() {

}

Screen::~Screen() {}

// ------------- Menu Screen ------------
menuScreen::~menuScreen() {
    FC_FreeFont(font);
}

void menuScreen::init(SDLWrapper* sdl) {
    font = FC_CreateFont();  
    FC_LoadFont(font, sdl->getRenderer(), "../fonts/ARIAL.TTF", 30, FC_MakeColor(255,255,255,255), TTF_STYLE_NORMAL); 
    std::cout << "Font Loaded!" << std::endl;

    addBodiesButton = Button(1195, 45, 170, 40, {0, 0, 0}, {0, 0, 0});

    textBoxFont = TTF_OpenFont("../fonts/ARIAL.TTF", 24);
    sunMassTextBox = TextBox(200, 50, 170, 35, sdl->getRenderer(), textBoxFont);
    SDL_StartTextInput();
}

void menuScreen::handleEvents(SDLWrapper* sdl, SDL_Event& event) {
    sunMassTextBox.handleEvent(event);

    for (auto& b : bodiesTextBoxes) {
        b.handleEvent(event);
    }

    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RETURN) {
                sdl->data.sunMass = sunMassTextBox.getText();
                sdl->changeState(ScreenID::Running);
            }
            break;
        default:
            break;
    }
    if (addBodiesButton.handleClick(event)) {
        sdl->data.bodies.push_back(Body(0, 0, 0, 0, 0));
        bodiesTextBoxes.push_back(TextBox(250, 85 + (30 * (sdl->data.bodies.size()-1)), 100, 30, sdl->getRenderer(), textBoxFont));
    }
}

void menuScreen::update(SDLWrapper* sdl) {}

void menuScreen::render(SDLWrapper* sdl) {
    addBodiesButton.render(sdl->getRenderer());

    //Draw the sunmass onto the screen
    FC_Draw(font, sdl->getRenderer(), 50, 50, "Sun Mass: %s \n", sdl->data.sunMass.c_str());

    sunMassTextBox.render();

    for (auto& b : bodiesTextBoxes) {
        b.render();
    }

    //Allow the user to add more bodies and change their mass
    FC_Draw(font, sdl->getRenderer(), 1200, 50, "Add Bodies");
    for(int i = 0; i < sdl->data.bodies.size(); i++) {
        FC_Draw(font, sdl->getRenderer(), 50, 85 + (30 * (i)), "Body %d - xPos: ", i+1);
    }
}

// ---------- Running Screen ------------
void runningScreen::init(SDLWrapper* sdlWrapper) {}

void runningScreen::handleEvents(SDLWrapper* sdlWrapper, SDL_Event& event) {}

void runningScreen::update(SDLWrapper* sdlWrapper) {}

void runningScreen::render(SDLWrapper* sdlWrapper) {}