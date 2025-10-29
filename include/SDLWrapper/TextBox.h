#include <SDLWrapper/shapeTextureWrapper.h>
#include <SDLWrapper/textureWrapper.h>


//Uses a shapeTextureWrapper object to create a textbox to listen for events 
class TextBox {
    public:
        //Initialize Variables
        TextBox();

        //Deallocate memory
        ~TextBox();

        //Create text box
        void createTextBox(int x, int y, int w, int h, SDL_Color boxColor);

        //Set font and color for the textbox
        void setFont(std::string fontPath, int fontSize, SDL_Color textColor);

        //Handle the text inputs
        void handleEvents(SDL_Renderer* renderer, SDL_Event& event);

        //Unselect the textbox
        void unselect();

        //Clear the textbox
        void clear(SDL_Renderer* renderer);

        //Deallocates the texture
        void free();

        //Renders textBox at a given point
        void render (SDL_Renderer *renderer);

        //Return the text in the textbox
        std::string getText();

    private:
        //The shapeTexture
        shapeTexture box;

        //The texture for the text inside the textbox
        Texture text;

        //The text stored as a string
        std::string stringText;

        //Check to see if the textbox is selected
        bool isSelected;

        static TextBox* activeTextbox;

        //The color of the text
        SDL_Color textColor;
};