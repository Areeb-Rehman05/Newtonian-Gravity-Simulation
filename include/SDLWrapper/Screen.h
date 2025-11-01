#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDLWrapper/SDLWrapper.h>
#include <SDLWrapper/textureWrapper.h>
#include <SDLWrapper/TextBox.h>
#include <SDLWrapper/Button.h>
#include <SDLWrapper/VectorPreview.h>
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
        virtual void free() = 0;
};

class menuScreen : public Screen {
    public:
        ~menuScreen();
        void init(SDLWrapper* sdl);
        void handleEvents(SDLWrapper* sdl, SDL_Event& event) override;
        void update(SDLWrapper* sdl) override;
        void render(SDLWrapper* sdl) override;
        void free();
    private:
        Texture sunMass;
        Texture bodyCount;

        TextBox sunMass_Input;
        TextBox bodyCount_Input;

        Button nextScreenButton;
};

class bodiesScreen : public Screen {
    public:
        ~bodiesScreen();
        void init(SDLWrapper* sdl);
        void handleEvents(SDLWrapper* sdl, SDL_Event& event) override;
        void update(SDLWrapper* sdl) override;
        void render(SDLWrapper* sdl) override;
        void free();
    private:
        int i;

        SDL_Color textColor;

        Texture bodyPositions;
        Texture bodyVectors;
        Texture mass;
        Texture scale;

        TextBox xpos, ypos, xvec, yvec, massInput;

        Button nextScreenButton;

        VectorPreview simGraph;
};

// class runningScreen : public Screen {
//     public:
//         ~runningScreen();
//         void init(SDLWrapper* sdl);
//         void handleEvents(SDLWrapper* sdl, SDL_Event& event) override;
//         void update(SDLWrapper* sdl) override;
//         void render(SDLWrapper* sdl) override;
//         void clean();

//     private:
// };