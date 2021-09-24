#include <curses.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <thread>

#include "Headers/boid.h"
#include "Headers/vec.h"
#include "Headers/draw.h"

int boidQty = 100;
double alignMod = 1.0;
double cohesionMod = 1.0;
double separationMod = 1.0;
double scale = 70;

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int main() {
    srand(time(NULL));

    initscr();

    std::vector<Boid> boids;
    for (int i = 0; i < boidQty; i++) {
        boids.push_back(Boid(RandomFloat(0, COLS * scale), RandomFloat(0, LINES * scale), 0, 0));
    }

    while (true) {
        clear();

        // Handle boids
        for (auto& b : boids) {
            b.edges();
            b.flock(boids);
            b.update();
            b.show();
        }

        refresh();
    }

    refresh();
    getch();
    endwin();

    return 0;
}
