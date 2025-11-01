#include <Simulations/BasicSimulation.h>

basicSimulation::basicSimulation(std::vector<Body> b, double sun) {
    allBodies = b;
    sunMass = sun;
}

basicSimulation::~basicSimulation() {

}

void basicSimulation::simulateBodyVelocity(double dt, Body &b) {
    Eigen::Vector2d acceleration;

    // A unit vector pointing from the body b towards the sun
    Eigen::Vector2d nHat = ((-b.position) / b.position.norm());

    // Very basic equation for acceleration where G is considered to be 1
    acceleration = (sunMass / pow(b.position.norm(), 2)) * nHat;

    b.velocity += acceleration * dt;
}