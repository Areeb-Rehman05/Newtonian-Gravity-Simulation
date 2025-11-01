#pragma once

#include <vector>
#include <memory>
#include <Simulations/Body.h>

class AbstractSimulation {
    protected:
        std::vector<Body> allBodies;
        double sunMass;

    public:

        AbstractSimulation();

        virtual ~AbstractSimulation();

        std::vector<Body> getBodies() const;

        virtual void simulateBodyVelocity(double dt, Body& b) = 0;

        void simulateBodyPosition(double dt, Body& b);

        void simulateFrame(double dt);
};