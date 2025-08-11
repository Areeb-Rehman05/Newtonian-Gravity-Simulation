#include <SDLWrapper/SDLWrapper.h>

SDLWrapper::SDLWrapper() {

}

SDLWrapper::~SDLWrapper() {

}

void SDLWrapper::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialized!" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window) {
            std::cout << "Window Created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer Created!" << std::endl;
        }
        isRunning = true;
        changeState(ScreenID::Menu);
        currentState.get()->init(this);
    } else {
        isRunning = false;
    }
}

void SDLWrapper::changeState(ScreenID newScreen) {
    switch (newScreen) {
        case ScreenID::Menu:
            currentState = std::make_unique<menuScreen>();
            break;
        case ScreenID::Running:
            currentState = std::make_unique<runningScreen>();
            currentState.get()->init(this);
            break;
    }
}

void SDLWrapper::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
    currentState->handleEvents(this, event);
}

void SDLWrapper::update() {
    currentState->update(this);
}

void SDLWrapper::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    currentState->render(this);
    SDL_RenderPresent(renderer);
}

SDL_Renderer* SDLWrapper::getRenderer() {
    return renderer;
}

void SDLWrapper::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    // FC_FreeFont(font);
    SDL_Quit();
    std::cout << "Program Cleaned" << std::endl;
}

bool SDLWrapper::running() {
    return isRunning;
}

