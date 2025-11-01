#include <Simulations/Body.h>

//Implementation of the Body class constructor
Body::Body(double xpos, double ypos, double xvec, double yvec, double m) {
    position = Eigen::Vector2d(xpos, ypos);
    velocity = Eigen::Vector2d(xvec, yvec);
    mass = m;
}

Eigen::Vector2d Body::getPosition() {
    return position;
}

Eigen::Vector2d Body::getVelocity() {
    return velocity;
}