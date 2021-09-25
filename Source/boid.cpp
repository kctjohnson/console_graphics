#include <curses.h>
#include <cmath>

#include "../Headers/draw.h"
#include "../Headers/boid.h"

extern double alignMod;
extern double cohesionMod;
extern double separationMod;
extern double scale;
extern double maxForce;
extern double maxSpeed;
extern double perception;

float RandomFloat(float a, float b);

Boid::Boid(double x, double y, double vx, double vy) : 
    position(x, y), velocity(vx, vy), acceleration(0, 0) {
    static int staticID = 0;
    this->id = staticID;
    this->velocity.x = RandomFloat(-100, 100);
    this->velocity.y = RandomFloat(-100, 100);
    this->velocity.setMag(RandomFloat(2, 4));
    staticID++;

}

void Boid::edges() {
    double imgnryWidth = (double)COLS * scale;
    double imgnryHeight = (double)LINES * scale;

    if (this->position.x > imgnryWidth) {
        this->position.x = 0;
    } else if (this->position.x < 0) {
        this->position.x = imgnryWidth;
    }

    if (this->position.y > imgnryHeight) {
        this->position.y = 0;
    } else if (this->position.y < 0) {
        this->position.y = imgnryHeight;
    }
}

void Boid::flock(std::vector<Boid> boids) {
    vec2d alignment(0, 0);
    vec2d cohesion(0, 0);
    vec2d separation(0, 0);

    int total = 0;
    for (auto b : boids) {
        double dist = this->position.dist(b.position);

        if (b.id != this->id && dist < perception && dist != 0) {
            alignment.add(b.velocity);

            cohesion.add(b.position);
            
            vec2d tmp = this->position.copy();
            tmp.sub(b.position);
            tmp.div(dist);
            separation.add(tmp);
            
            total++;
        }
    }

    if (total > 0) {
        alignment.div(total);
        alignment.setMag(maxSpeed);
        alignment.sub(this->velocity);
        alignment.limit(maxForce);

        cohesion.div(total);
        cohesion.sub(this->position);
        cohesion.setMag(maxSpeed);
        cohesion.sub(this->velocity);
        cohesion.limit(maxForce);

        separation.div(total);
        separation.setMag(maxSpeed);
        separation.sub(this->velocity);
        separation.limit(maxForce);
    }

    alignment.mult(alignMod);
    cohesion.mult(cohesionMod);
    separation.mult(separationMod);

    this->acceleration.add(alignment);
    this->acceleration.add(cohesion);
    this->acceleration.add(separation);
}

void Boid::update() {
    this->position.add(this->velocity);
    this->velocity.add(this->acceleration);
    this->velocity.limit(maxSpeed);
    this->acceleration.mult(0);
}

void Boid::show() {
    int showX = (int)(this->position.x / scale);
    int showY = (int)(this->position.y / scale);

    if (fabs(this->velocity.x) > fabs(this->velocity.y)) {
        if (this->velocity.x > 0) {
            Point(showX, showY, '>');
        } else {
            Point(showX, showY, '<');
        }
    } else {
        if (this->velocity.y > 0) {
            Point(showX, showY, 'v');
        } else {
            Point(showX, showY, '^');
        }
    }
}

