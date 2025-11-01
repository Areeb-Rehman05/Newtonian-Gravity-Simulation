#pragma once

#include <Simulations/AbstractSimulation.h>

class advancedSimulation : public AbstractSimulation {
    public:
        advancedSimulation();

        ~advancedSimulation();

        void init(std::vector<Body> b, double sunMass);

        void simulateBodyVelocity(double dt, Body& b) override;
};