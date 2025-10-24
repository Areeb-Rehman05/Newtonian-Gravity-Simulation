#include <SDLWrapper/SDLWrapper.h>

SDLWrapper::SDLWrapper() {

}

SDLWrapper::~SDLWrapper() {

}

void SDLWrapper::init(std::string title, int width, int height) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Creat the window
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if(window == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        } else {
            //Create renderer from window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL) {
                printf("Renderer could not be created! SDL_Error: %s", SDL_GetError());
            } else {
                //Initialize PNG Loading (Only important if we want to make a custom button, might make it in paint.net)
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_Image could not initialize! SDLImage_Error: %s", IMG_GetError());
                }

                //Initialize SDL_TTF font loading 
                if(TTF_Init() == -1) {
                    printf("SDL_TFF could not intitialize! SDL_TTF Error: %s\n", TTF_GetError());
                }
                isRunning = true;
                SCREEN_WIDTH = width;
                SCREEN_HEIGHT = height;
                changeState(ScreenID::Menu);
            }
        }
    }
}

void SDLWrapper::changeState(ScreenID newScreen) {
    switch (newScreen) {
        case ScreenID::Menu:
            currentScreen = new menuScreen();
            currentScreen->init(this);
            break;
        case ScreenID::Running:
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
    currentScreen->handleEvents(this, event);
}

void SDLWrapper::update() {
    currentScreen->update(this);
}

void SDLWrapper::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    currentScreen->render(this);
    SDL_RenderPresent(renderer);
}

SDL_Renderer* SDLWrapper::getRenderer() {
    return renderer;
}

void SDLWrapper::clean() {
    currentScreen->clean();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool SDLWrapper::running() {
    return isRunning;
}

int SDLWrapper::getScreenWidth() {
    return SCREEN_WIDTH;
}

int SDLWrapper::getScreenHeight() {
    return SCREEN_HEIGHT;
}