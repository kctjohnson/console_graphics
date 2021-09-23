#include <curses.h>
#include <stdlib.h>
#include <math.h>

#include "Headers/boid.h"
#include "Headers/vec.h"
#include "Headers/draw.h"

int boidQty = 150;

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
        boids.push_back(Boid(RandomFloat(0, COLS * 100), RandomFloat(0, LINES * 100), 0, 0));
    }

    while (true) {
        clear();
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
