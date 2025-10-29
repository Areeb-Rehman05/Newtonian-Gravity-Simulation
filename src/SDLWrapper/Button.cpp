#include <SDLWrapper/Button.h>

Button::Button() {

}

Button::~Button() {
    free();
}

void Button::createButton(int x, int y, int w, int h, SDL_Color boxColor) {
    box.setDimensions(x, y, w, h);
    box.setColor(boxColor.r, boxColor.g, boxColor.b, boxColor.a);
}

void Button::setFont(std::string fontPath, int fontSize, SDL_Color textColor) {
    text.setFont(fontPath, fontSize);

    this->textColor = textColor;
}

void Button::setText(std::string buttonText, SDL_Renderer* renderer) {
    text.loadFromRenderedText(buttonText, textColor, renderer);
}

bool Button::handleClick(SDL_Renderer* renderer, SDL_Event& event) {
    if(box.isHovering()) {
        box.setColor(128, 128, 128, 255);

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                return true;
            }
        }
    } else {
        box.setColor(255, 255, 255, 255);
    }
    return false;
}

void Button::free() {
    text.free();
    box.free();
}

void Button::render(SDL_Renderer* renderer) {
    box.render(renderer);
    text.render(box.getRect().x + ((box.getRect().w - text.getWidth()) / 2), (box.getRect().y + (box.getRect().h - text.getHeight()) / 2), renderer);
}