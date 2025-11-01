#pragma once

#include <Simulations/AbstractSimulation.h>

class basicSimulation : public AbstractSimulation {
    public:

        basicSimulation(std::vector<Body> b, double sunMass);

        ~basicSimulation();

        void simulateBodyVelocity(double dt, Body& b) override;
};