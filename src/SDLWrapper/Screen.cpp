#include <SDLWrapper/Screen.h>



Screen::Screen() {

}

Screen::~Screen() {}

// ------------- Menu Screen ------------
menuScreen::~menuScreen() {
    free();
}

void menuScreen::init(SDLWrapper* sdl) {
    SDL_Color textColor = {255, 255, 255};
    sunMass.setFont("../fonts/ARIAL.TTF", 28);
    sunMass.loadFromRenderedText("Sun Mass: ", textColor, sdl->getRenderer());

    bodyCount.setFont("../fonts/ARIAL.TTF", 28);
    bodyCount.loadFromRenderedText("Body Count: ", textColor, sdl->getRenderer());

    sunMass_Input.createTextBox(250, 50, 150, 30, {255, 255, 255, 255});
    sunMass_Input.setFont("../fonts/ARIAL.TTF", 28, {0, 0, 0, 255});

    bodyCount_Input.createTextBox(260, 100, 150, 30, {255, 255, 255, 255});
    bodyCount_Input.setFont("../fonts/ARIAL.TTF", 28, {0, 0, 0, 255});

    nextScreenButton.createButton(1000, 50, 150, 30, {255, 255, 255, 255});
    nextScreenButton.setFont("../fonts/ARIAL.TTF", 28, {0, 0, 0, 255});
    nextScreenButton.setText("Submit!", sdl->getRenderer());
}

void menuScreen::handleEvents(SDLWrapper* sdl, SDL_Event& event) {
    sunMass_Input.handleEvents(sdl->getRenderer(), event);
    bodyCount_Input.handleEvents(sdl->getRenderer(), event);

    if(nextScreenButton.handleClick(sdl->getRenderer(), event)) {
        sdl->sharedData.sunMass = std::stoi(sunMass_Input.getText());
        sdl->sharedData.totalBodies = std::stoi(bodyCount_Input.getText());
        sdl->changeState(ScreenID::Bodies);
    }
}

void menuScreen::update(SDLWrapper* sdl) {

}

void menuScreen::render(SDLWrapper* sdl) {
    sunMass.render(100, 50, sdl->getRenderer());
    bodyCount.render(100, 100, sdl->getRenderer());

    sunMass_Input.render(sdl->getRenderer());
    bodyCount_Input.render(sdl->getRenderer());

    nextScreenButton.render(sdl->getRenderer());
}

void menuScreen::free() {
    sunMass.free();
    bodyCount.free();

    sunMass_Input.free();
    bodyCount_Input.free();

    nextScreenButton.free();
}

// ----------- Bodies Screen ----------
bodiesScreen::~bodiesScreen() {
    free();
}

void bodiesScreen::init(SDLWrapper* sdl) {
    i = 1;

    textColor = {255, 255, 255};
    bodyPositions.setFont("../fonts/ARIAL.TTF", 28);
    bodyPositions.loadFromRenderedText("Body " + std::to_string(i) + " Positions(x, y): ", textColor, sdl->getRenderer());

    bodyVectors.setFont("../fonts/ARIAL.TTF", 28);
    bodyVectors.loadFromRenderedText("Body " + std::to_string(i) + " Vectors(x, y): ", textColor, sdl->getRenderer());

    mass.setFont("../fonts/ARIAL.TTF", 28);
    mass.loadFromRenderedText("Body " + std::to_string(i) + " Mass: ", textColor, sdl->getRenderer());

    scale.setFont("../fonts/ARIAL.TTF", 28);

    xpos.createTextBox(500, 50, 75, 30, {255, 255, 255, 255});
    xpos.setFont("../fonts/ARIAL.TTF", 28, {0, 0, 0, 255});

    ypos.createTextBox(600, 50, 75, 30, {255, 255, 255, 255});
    ypos.setFont("../fonts/ARIAL.TTF", 28, {0, 0, 0, 255});

    xvec.createTextBox(500, 100, 75, 30, {255, 255, 255, 255});
    xvec.setFont("../fonts/ARIAL.TTF", 28, {0, 0, 0, 255});

    yvec.createTextBox(600, 100, 75, 30, {255, 255, 255, 255});
    yvec.setFont("../fonts/ARIAL.TTF", 28, {0, 0, 0, 255});

    massInput.createTextBox(500, 150, 150, 30, {255, 255, 255, 255});
    massInput.setFont("../fonts/ARIAL.TTF", 28, {0, 0, 0, 255});

    nextScreenButton.createButton(1000, 50, 300, 30, {255, 255, 255, 255});
    nextScreenButton.setFont("../fonts/ARIAL.TTF", 28, {0, 0, 0, 255});
    nextScreenButton.setText("Submit!", sdl->getRenderer());

    simGraph.init(100, 250, 600, 600);
}

void bodiesScreen::handleEvents(SDLWrapper* sdl, SDL_Event& event) {
    xpos.handleEvents(sdl->getRenderer(), event);
    ypos.handleEvents(sdl->getRenderer(), event);
    xvec.handleEvents(sdl->getRenderer(), event);
    yvec.handleEvents(sdl->getRenderer(), event);
    massInput.handleEvents(sdl->getRenderer(), event);

    if(nextScreenButton.handleClick(sdl->getRenderer(), event)) {
        if(i < sdl->sharedData.totalBodies && xpos.getText() != "" && ypos.getText() != "" && xvec.getText() != "" && yvec.getText() != "" && massInput.getText() != "") {
            int xPosition = std::stoi(xpos.getText());
            int yPosition = std::stoi(ypos.getText());
            int xVector = std::stoi(xvec.getText());
            int yVector = std::stoi(yvec.getText());
            int bodyMass = std::stoi(massInput.getText());

            Body newBody(xPosition, yPosition, xVector, yVector, bodyMass);

            sdl->sharedData.bodies.push_back(newBody);
            scale.loadFromRenderedText("Scale: " + simGraph.getScale(), textColor, sdl->getRenderer());

            i++; 
            bodyPositions.loadFromRenderedText("Body " + std::to_string(i) + " Positions(x, y): ", textColor, sdl->getRenderer());
            bodyVectors.loadFromRenderedText("Body " + std::to_string(i) + " Vectors(x, y): ", textColor, sdl->getRenderer());
            mass.loadFromRenderedText("Body " + std::to_string(i) + " Mass: ", textColor, sdl->getRenderer());

            xpos.clear(sdl->getRenderer());
            ypos.clear(sdl->getRenderer());
            xvec.clear(sdl->getRenderer());
            yvec.clear(sdl->getRenderer());
            massInput.clear(sdl->getRenderer());
        } else if (i >= sdl->sharedData.totalBodies) {
            int xPosition = std::stoi(xpos.getText());
            int yPosition = std::stoi(ypos.getText());
            int xVector = std::stoi(xvec.getText());
            int yVector = std::stoi(yvec.getText());
            int bodyMass = std::stoi(massInput.getText());

            Body newBody(xPosition, yPosition, xVector, yVector, bodyMass);

            sdl->sharedData.bodies.push_back(newBody);

            sdl->changeState(ScreenID::Running);
        }
    }
}

void bodiesScreen::update(SDLWrapper* sdl) {
    simGraph.updateData(sdl->sharedData.bodies);
    scale.loadFromRenderedText("Scale: " + std::to_string(simGraph.getScale()), textColor, sdl->getRenderer());

    if (i >= sdl->sharedData.totalBodies) {
        nextScreenButton.setText("Start Simulation!", sdl->getRenderer());
    }
}

void bodiesScreen::render(SDLWrapper* sdl) {
    bodyPositions.render(100, 50, sdl->getRenderer());
    bodyVectors.render(100, 100, sdl->getRenderer());
    mass.render(100, 150, sdl->getRenderer());
    scale.render(1000, 750, sdl->getRenderer());

    xpos.render(sdl->getRenderer());
    ypos.render(sdl->getRenderer());
    xvec.render(sdl->getRenderer());
    yvec.render(sdl->getRenderer());
    massInput.render(sdl->getRenderer());

    nextScreenButton.render(sdl->getRenderer());

    simGraph.render(sdl->getRenderer());
}

void bodiesScreen::free() {
    bodyPositions.free();
    bodyVectors.free();
    mass.free();
    scale.free();
    xpos.free();
    ypos.free();
    xvec.free();
    yvec.free();
    massInput.free();

    nextScreenButton.free();

    simGraph.free();
}

// ----------- Running Screen ----------

runningScreen::~runningScreen() {
    free();
}

void runningScreen::init(SDLWrapper* sdl) {
    sim.init(sdl->sharedData.bodies, sdl->sharedData.sunMass);

    bodyPositions.clear();
    bodyPositions.resize(sim.getBodies().size());
}

void runningScreen::handleEvents(SDLWrapper* sdl, SDL_Event& event) {

}

void runningScreen::update(SDLWrapper* sdl) {
    int count = 0;
    for(auto &body : sim.getBodies()) {
        Point temp = {body.getPosition().x(), body.getPosition().y()};
        bodyPositions[count].push_back(temp);
        count++;
    }
    sim.simulateFrame(0.05);
}

void runningScreen::render(SDLWrapper* sdl) {
    //Clear the screen
    SDL_SetRenderDrawColor(sdl->getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(sdl->getRenderer());

    //Render the sun in the center of the simulation
    SDL_SetRenderDrawColor(sdl->getRenderer(), 255, 255, 255, 255);
    SDL_Rect sunRect = {720, 450, sdl->sharedData.sunMass/400 + 4, sdl->sharedData.sunMass/400 + 4};
    SDL_RenderDrawRect(sdl->getRenderer(), &sunRect);

    //Draw the points on the screen
    int count = 0;
    for (auto &body : sim.getBodies()) {
        SDL_Color color = bodyColors[count % 7];

        SDL_SetRenderDrawColor(sdl->getRenderer(), color.r, color.g, color.b, color.a);

        for (const auto &p : bodyPositions[count]) {
            SDL_RenderDrawPoint(sdl->getRenderer(), static_cast<int>(p.first) + 720, static_cast<int>(p.second) + 450 );
        }

        count++;
    }  
}

void runningScreen::free() {
    
}