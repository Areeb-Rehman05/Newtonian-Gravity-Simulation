#include <SDLWrapper/SDLWrapper.h>

SDLWrapper::SDLWrapper() {

}

SDLWrapper::~SDLWrapper() {

}

void SDLWrapper::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    stage = 1;
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
        font = FC_CreateFont();  
        FC_LoadFont(font, renderer, "../fonts/ARIAL.TTF", 30, FC_MakeColor(255,255,255,255), TTF_STYLE_NORMAL); 
    } else {
        isRunning = false;
    }
}

void SDLWrapper::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_TEXTINPUT:
            if(isdigit(event.text.text[0])) {
                sunMass += event.text.text;
            }
            break;

        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_BACKSPACE && !sunMass.empty()) {
                sunMass.pop_back();
            } else if (event.key.keysym.sym == SDLK_RETURN) {
                    stage = 2;  
            }
            break;

        default:
        
            break;
    }
}

void SDLWrapper::update() {
    if (stage == 2) {

    }
}

void SDLWrapper::render() {
    SDL_RenderClear(renderer);
    //this is where we would add stuff to render
    std::string inputFields = "";
    switch (stage) {
        case 1:
            //Draw the sunmass onto the screen
            FC_Draw(font, renderer, 50, 50, "Sun Mass: %s \n", sunMass.c_str());

            //Allow the user to add more bodies and change their mass
            FC_Draw(font, renderer, 400, 80, "Add Bodies");
            for(int i = 0; i < bodyNums; i++) {
                inputFields += "Body " + std::to_string(i+1) + "\n";
            }
            FC_Draw(font, renderer, 50, 80, inputFields.c_str());
            break;
        case 2:

        default:
            break;
    }
    SDL_RenderPresent(renderer);
}

void SDLWrapper::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    FC_FreeFont(font);
    SDL_Quit();
    std::cout << "Program Cleaned" << std::endl;
}

bool SDLWrapper::running() {
    return isRunning;
}

