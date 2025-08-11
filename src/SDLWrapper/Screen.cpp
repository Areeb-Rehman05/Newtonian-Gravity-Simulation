#include <SDLWrapper/Screen.h>

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

    addBodiesButton = Button(395, 75, 170, 40, {0, 0, 0}, {0, 0, 0});
}

void menuScreen::handleEvents(SDLWrapper* sdl, SDL_Event& event) {
    switch (event.type) {
        case SDL_TEXTINPUT:
            if(isdigit(event.text.text[0])) {
                sdl->data.sunMass += event.text.text;
            }
            break;

        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_BACKSPACE && !sdl->data.sunMass.empty()) {
                sdl->data.sunMass.pop_back();
            } else if (event.key.keysym.sym == SDLK_RETURN) {

                sdl->changeState(ScreenID::Running);
            }
            break;
        default:
            break;
    }
    if (addBodiesButton.handleClick(event)) {
        sdl->data.bodyNums++;
    }
}

void menuScreen::update(SDLWrapper* sdl) {}

void menuScreen::render(SDLWrapper* sdl) {
    std::string inputFields;

    addBodiesButton.render(sdl->getRenderer());

    //Draw the sunmass onto the screen
    FC_Draw(font, sdl->getRenderer(), 50, 50, "Sun Mass: %s \n", sdl->data.sunMass.c_str());

    //Allow the user to add more bodies and change their mass
    FC_Draw(font, sdl->getRenderer(), 400, 80, "Add Bodies");
    for(int i = 0; i < sdl->data.bodyNums; i++) {
        inputFields += "Body " + std::to_string(i+1) + "\n";
    }
    FC_Draw(font, sdl->getRenderer(), 50, 80, inputFields.c_str());
}

// ---------- Running Screen ------------
void runningScreen::init(SDLWrapper* sdlWrapper) {}

void runningScreen::handleEvents(SDLWrapper* sdlWrapper, SDL_Event& event) {}

void runningScreen::update(SDLWrapper* sdlWrapper) {}

void runningScreen::render(SDLWrapper* sdlWrapper) {}