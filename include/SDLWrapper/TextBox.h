#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextBox {
public:
    TextBox(int x, int y, int w, int h, SDL_Renderer* renderer, TTF_Font* font)
        : rect{x, y, w, h}, renderer(renderer), font(font), text(""), cursorPos(0) {
        textColor = {255, 255, 255, 255};   // Black text
        bgColor   = {128, 128, 128, 255}; // White background
        borderColor = {0, 0, 0, 255}; // Black border
    }

    void handleEvent(const SDL_Event& e) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mx = e.button.x;
            int my = e.button.y;
            focused = (mx > rect.x && mx < rect.x + rect.w && 
                       my > rect.y && my < rect.y + rect.h);
        }
        if (focused) {
            if (e.type == SDL_TEXTINPUT) {
                text.insert(cursorPos, e.text.text);
                cursorPos += strlen(e.text.text);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && cursorPos > 0) {
                    text.erase(cursorPos - 1, 1);
                    cursorPos--;
                } else if (e.key.keysym.sym == SDLK_LEFT && cursorPos > 0) {
                    cursorPos--;
                } else if (e.key.keysym.sym == SDLK_RIGHT && cursorPos < (int)text.size()) {
                    cursorPos++;
                }
            }
        }
    }

    void render() {
        // Draw background
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderFillRect(renderer, &rect);

        // Draw border
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_RenderDrawRect(renderer, &rect);

        // Render text
        if (!text.empty()) {
            SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), textColor);
            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_Rect dst = {rect.x + 5, rect.y + (rect.h - surf->h) / 2, surf->w, surf->h};
            SDL_RenderCopy(renderer, tex, NULL, &dst);
            SDL_DestroyTexture(tex);
            SDL_FreeSurface(surf);
        }

        // Draw cursor if focused
        if (focused) {
            int cursorX = rect.x + 5;
            if (!text.empty()) {
                std::string beforeCursor = text.substr(0, cursorPos);
                SDL_Surface* surf = TTF_RenderText_Blended(font, beforeCursor.c_str(), textColor);
                cursorX += surf->w;
                SDL_FreeSurface(surf);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawLine(renderer, cursorX, rect.y + 5, cursorX, rect.y + rect.h - 5);
        }
    }
    
    std::string getText() const { return text; }

private:
    SDL_Rect rect;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color textColor, bgColor, borderColor;
    std::string text;
    bool focused = false;
    int cursorPos;
};
