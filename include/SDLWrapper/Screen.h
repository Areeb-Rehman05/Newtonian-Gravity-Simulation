#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDLWrapper/SDLWrapper.h>
#include <SDLWrapper/textureWrapper.h>
#include <string>

class SDLWrapper;

class Screen {
    public:
        Screen();
        ~Screen();
        virtual void init(SDLWrapper* sdl) = 0;
        virtual void handleEvents(SDLWrapper* sdl, SDL_Event& event) = 0;
        virtual void update(SDLWrapper* sdl) = 0;
        virtual void render(SDLWrapper* sdl) = 0;
        virtual void clean() = 0;
};

class menuScreen : public Screen {
    public:
        ~menuScreen();
        void init(SDLWrapper* sdl);
        void handleEvents(SDLWrapper* sdl, SDL_Event& event) override;
        void update(SDLWrapper* sdl) override;
        void render(SDLWrapper* sdl) override;
        void clean();
    private:
        Texture sunMass;
        Texture textBox;
};