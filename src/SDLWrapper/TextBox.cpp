#include <SDLWrapper/TextBox.h>

TextBox* TextBox::activeTextbox = nullptr;

TextBox::TextBox() {
    stringText = "";
}

TextBox::~TextBox() {
    text.free();
}

void TextBox::createTextBox(int x, int y, int w, int h, SDL_Color boxColor) {
    box.setDimensions(x, y, w, h);
    box.setColor(boxColor.r, boxColor.g, boxColor.b, boxColor.a);
}

void TextBox::setFont(std::string fontPath, int fontSize, SDL_Color textColor) {
    text.setFont(fontPath, fontSize);

    this->textColor = textColor;
}

void TextBox::handleEvents(SDL_Renderer* renderer, SDL_Event& event) {
    if(box.isHovering() || isSelected) {
        box.setColor(128, 128, 128, 255);
    } else {
        box.setColor(255, 255, 255, 255);
    }

    if (box.isHovering()) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                if(activeTextbox == nullptr) {
                    isSelected = true;
                    activeTextbox = this;
                } else {
                    activeTextbox->unselect();
                    isSelected = true;
                    activeTextbox = this;
                }
            }
        }
    } else {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            if (isSelected) {
                unselect();
                if (activeTextbox == this)
                    activeTextbox = nullptr;
            }
        }
    }

    if (isSelected) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) {
                stringText += static_cast<char>('0' + (event.key.keysym.sym - SDLK_0));
                text.loadFromRenderedText(stringText, textColor, renderer);
            } else if (event.key.keysym.sym == SDLK_BACKSPACE && stringText.length() > 0) {
                stringText.pop_back();
                text.loadFromRenderedText(stringText, textColor, renderer);
            }
        }
    }
}

void TextBox::unselect() {
    isSelected = false;
}

void TextBox::clear(SDL_Renderer* renderer) {
    stringText = "";
    text.loadFromRenderedText(stringText, textColor, renderer);
}

void TextBox::free() {
    text.free();
    box.free();

    stringText.clear();
    isSelected = false;

    if (activeTextbox == this) {
        activeTextbox = nullptr;
    }
}

void TextBox::render(SDL_Renderer* renderer) {
    box.render(renderer);
    text.render(box.getRect().x, box.getRect().y, renderer);
}

std::string TextBox::getText() {
    return stringText;
}