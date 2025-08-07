#include <../include/SDLWrapper/SDLWrapper.h>

SDLWrapper *program = nullptr;

int main () {
    program = new SDLWrapper();

    program->init("Newtonian Gravity Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 900, false);

    while(program->running()) {
        program->handleEvents();
        program->update();
        program->render();
    }

    program->clean();

    return 0;
}