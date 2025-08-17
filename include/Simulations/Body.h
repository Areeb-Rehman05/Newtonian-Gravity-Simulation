#pragma once

#include <eigen3/Eigen/Dense>

//Class that represents a celestial body
class Body {
    public :
        Eigen::Vector2d position; 
        Eigen::Vector2d velocity;
        double mass;

        Body (double xpos, double ypos, double xvec, double yvec, double m);
};