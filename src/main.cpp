#include <../include/SDLWrapper/SDLWrapper.h>

SDLWrapper *program = nullptr;

int main () {
    program = new SDLWrapper();

    program->init("Newtonian Gravity Simulation", 1440, 900);

    while(program->running()) {
        program->handleEvents();
        program->update();
        program->render();
    }

    program->clean();

    return 0;
}