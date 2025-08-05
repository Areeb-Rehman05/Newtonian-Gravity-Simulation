#include <Simulations/AdvancedSimulation.h>

advancedSimulation::advancedSimulation(std::vector<std::shared_ptr<Body>> b, double sun) {
    allBodies = b;
    sunMass = sun;
}

advancedSimulation::~advancedSimulation() {
    //Doesn't have to do anything because shared_ptr already cleans up everything :D
}

void advancedSimulation::simulateBodyVelocity(double dt, Body &b) {
    Eigen::Vector2d acceleration;

    // A unit vector pointing from the body b towards the sun
    Eigen::Vector2d nHat = ((-b.position) / b.position.norm());

    // Very basic equation for acceleration towards the sun where G is considered to be 1
    acceleration = (sunMass / pow(b.position.norm(), 2)) * nHat;

    for (auto &body : allBodies)
    {
        if (&b != body.get())
        {
            Eigen::Vector2d r = body->position - b.position;
            double distance = r.norm();
            Eigen::Vector2d rHat = ((r) / distance);

            acceleration += ((body->mass / std::pow(distance, 2)) * rHat);
        }
    }

    b.velocity += acceleration * dt;
}