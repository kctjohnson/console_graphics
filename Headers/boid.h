#pragma once

#include <vector>

#include "../Headers/vec.h"

extern const int width;
extern const int height;

class Boid {
public:
    vec2d position;
    vec2d velocity;
    vec2d acceleration;
    int id;

    Boid(double x, double y, double vx, double vy);

    void edges();
    void flock(std::vector<Boid> boids);
    
    void update();
    void show();
};
