#pragma once

#include <vector>

#include "../Headers/vec.h"

extern const int width;
extern const int height;

const double maxForce = 0.2;
const double maxSpeed = 6;
const double perception = 500;

class Boid {
public:
    vec2d position;
    vec2d velocity;
    vec2d acceleration;
    int id;

    Boid(double x, double y, double vx, double vy);

    void edges();
    vec2d align(std::vector<Boid> boids);
    vec2d cohesion(std::vector<Boid> boids);
    vec2d separation(std::vector<Boid> boids);
    void flock(std::vector<Boid> boids);
    
    void update();
    void show();
};
