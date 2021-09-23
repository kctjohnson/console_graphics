#include <curses.h>
#include <stdlib.h>
#include <math.h>

#include "Headers/boid.h"
#include "Headers/vec.h"
#include "Headers/draw.h"

int boidQty = 150;

struct Vec {
    int x;
    int y;
};

int main() {
    initscr();

    std::vector<Boid> boids;
    for (int i = 0; i < boidQty; i++) {
        boids.push_back(Boid(100 + i * 100, 500, 0, 0));
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
