#pragma once

#include <SDL2/SDL.h>
#include <SDL_FontCache/SDL_FontCache.h>
#include <SDLWrapper/SDLWrapper.h>
#include <Simulations/AdvancedSimulation.h>
#include <string>
#include <SDLWrapper/Button.h>
#include <SDL2/SDL_ttf.h>

class SDLWrapper;

class Screen {
    public:
        Screen();
        ~Screen();
        virtual void init(SDLWrapper* sdl) = 0;
        virtual void handleEvents(SDLWrapper* sdl, SDL_Event& event) = 0;
        virtual void update(SDLWrapper* sdl) = 0;
        virtual void render(SDLWrapper* sdl) = 0;
};

class menuScreen : public Screen {
    public:
        ~menuScreen();
        void init(SDLWrapper* sdl);
        void handleEvents(SDLWrapper* sdl, SDL_Event& event) override;
        void update(SDLWrapper* sdl) override;
        void render(SDLWrapper* sdl) override;
    private:
        FC_Font* font;
        Button addBodiesButton{0,0,0,0, {0,0,0}, {0,0,0}};
};

class runningScreen : public Screen {
    public:
        void init(SDLWrapper* sdl);
        void handleEvents(SDLWrapper* sdl, SDL_Event& event) override;
        void update(SDLWrapper* sdl) override;
        void render(SDLWrapper* sdl) override;
};