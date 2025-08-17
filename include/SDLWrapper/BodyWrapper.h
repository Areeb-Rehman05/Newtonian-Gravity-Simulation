#pragma once

#include <SDLWrapper/TextBox.h>
#include <vector>

class BodyWrapper {
    public:
        BodyWrapper();

        void render();

        std::vector<std::string> getParams() {return {xPos,yPos,xVec,yVec};}

    private:
        std::string xPos, yPos, xVec, yVec;
        std::vector<TextBox> params;
};