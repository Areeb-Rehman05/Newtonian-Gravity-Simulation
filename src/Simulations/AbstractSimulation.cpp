#include <Simulations/AbstractSimulation.h>

AbstractSimulation::AbstractSimulation() {

}

AbstractSimulation::~AbstractSimulation() {
    
}

std::vector<Body> AbstractSimulation::getBodies() const {
    return allBodies;
}

void AbstractSimulation::simulateBodyPosition(double dt, Body& b) {
    b.position += b.velocity * dt;
}

void AbstractSimulation::simulateFrame(double dt) {
    for(auto& body : allBodies) {
        simulateBodyVelocity(dt, body);
    }
    for(auto& body : allBodies) {
        simulateBodyPosition(dt, body);
    }
}