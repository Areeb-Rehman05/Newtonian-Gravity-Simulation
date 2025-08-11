#pragma once

#include <SDL2/SDL.h>
#include <string>

class Button {
    public:
        Button(int xpos, int ypos, int width, int height, SDL_Color normal, SDL_Color hover) {
            rect = {xpos, ypos, width, height};
            colorNormal = normal;
            colorHover = hover;
        }

        void render(SDL_Renderer* renderer) {
            if(isHovering) {
                SDL_SetRenderDrawColor(renderer, colorHover.r, colorHover.g, colorHover.b, 255);
                SDL_RenderFillRect(renderer, &rect);
            } else if (!isHovering) {
                SDL_SetRenderDrawColor(renderer, colorNormal.r, colorNormal.g, colorNormal.b, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        bool handleClick(SDL_Event& event) {
            if (event.type == SDL_MOUSEMOTION) {
                int mx = event.motion.x;
                int my = event.motion.y;
                isHovering = (mx > rect.x && mx < rect.x + rect.w && my > rect.y && my < rect.y + rect.h);
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && isHovering) {
                return true;
            }
            return false;
        }

    private:
        SDL_Rect rect;
        SDL_Color colorNormal;
        SDL_Color colorHover;
        bool isHovering = false;
};