#include <Simulations/Body.h>

//Implementation of the Body class constructor
Body::Body(double x, double y, double m) {
    position = Eigen::Vector2d(x, y);
    velocity = Eigen::Vector2d::Zero();
    mass = m;
}