#include <SDLWrapper/SDLWrapper.h>
#include <stdexcept>

std::vector<SDL_Color> colors = {
    {255, 0, 0, 255},    // Red
    {0, 255, 0, 255},    // Green
    {0, 0, 255, 255},    // Blue
    {255, 255, 0, 255},  // Yellow
    {0, 255, 255, 255},  // Cyan
    {255, 0, 255, 255},  // Magenta
    {255, 165, 0, 255},  // Orange
    {128, 0, 128, 255},  // Purple
};

SDLWrapper::SDLWrapper() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    int screenWidth = displayMode.w;
    int screenHeight = displayMode.h;

    SDL_CreateWindowAndRenderer(static_cast<int>(screenWidth*0.75), static_cast<int>(screenHeight*0.75), 0, &window, &renderer);

    font = TTF_OpenFont("/home/areeb-pc/coding-projects/solar2/fonts/ARIAL.TTF", 28);
}

SDLWrapper::~SDLWrapper() {
}

void SDLWrapper::createTextLabel(const std::string& text, int x, int y, int w, int h) {
    SDL_Color White = {255, 255, 255};
    SDL_Surface* label = TTF_RenderText_Solid(font, text.c_str(), White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, label);
    SDL_Rect rect = {x, y, w, h};
    SDL_FreeSurface(label);
    SDL_RenderCopy(renderer, Message, NULL, &rect);
    SDL_RenderPresent(renderer);
}

void SDLWrapper::createTextBox(int x, int y, int w, int h) {
    SDL_Color boxColor = {40, 40, 40, 255};

    // Draw text box rectangle
    SDL_Rect inputBox = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, boxColor.r, boxColor.g, boxColor.b, boxColor.a);
    SDL_RenderFillRect(renderer, &inputBox);
}

void SDLWrapper::mapPoints(const std::vector<std::vector<Point>>& points_array) {
    //Make the background black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    SDL_Event e;
    bool quit = false;

    for(int i = 0; i < points_array[0].size() && !quit; i++) {
        // Check for events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }

        for(int j = 0; j < points_array.size(); j++) {
            // Generate a distinct color for each point set (based on j)
            SDL_Color color = colors[j % colors.size()];
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderDrawPoint(renderer, points_array[j][i].first, points_array[j][i].second);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10); //slow down rendering
    }

    bool running = true;
    SDL_Event event;

    while(running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Log("Quit event received");
                running = false;
            }
        }

        SDL_Delay(16);
    }

    SDL_Quit();
}

void SDLWrapper::listenForInput() {
    std::string numberInput = "";
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color boxColor = {40, 40, 40, 255};

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_TEXTINPUT) {
                if (isdigit(event.text.text[0])) {
                    numberInput += event.text.text;
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && !numberInput.empty()) {
                    numberInput.pop_back();
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    running = false;  
                }
            }
        }

        // Draw text box rectangle
        SDL_Rect inputBox = {400, 80, 300, 40};
        SDL_SetRenderDrawColor(renderer, boxColor.r, boxColor.g, boxColor.b, boxColor.a);
        SDL_RenderFillRect(renderer, &inputBox);

        // Render input text
        if (!numberInput.empty()) {
            SDL_Surface* surface = TTF_RenderText_Blended(font, numberInput.c_str(), white);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect dst = {inputBox.x + 10, inputBox.y + 5, surface->w, surface->h};
            SDL_FreeSurface(surface);
            SDL_RenderCopy(renderer, texture, nullptr, &dst);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);
}

void SDLWrapper::constructApp() {
    createTextLabel("Sun Mass", 50, 80, 300, 40);

    createTextBox(400, 80, 300, 40);

    listenForInput();

    SDL_Delay(10000);
}