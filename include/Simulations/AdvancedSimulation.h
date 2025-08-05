#pragma once

#include <Simulations/AbstractSimulation.h>

class advancedSimulation : public AbstractSimulation {
    public:
        advancedSimulation(std::vector<std::shared_ptr<Body>> b, double sunMass);

        ~advancedSimulation();

        void simulateBodyVelocity(double dt, Body& b) override;
};