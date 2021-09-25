#include <curses.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <thread>

#include "Headers/boid.h"
#include "Headers/vec.h"
#include "Headers/draw.h"

double maxForce = 0.2;
double maxSpeed = 10;
double perception = 300;

int boidQty = 1000;
double alignMod = 1.0;
double cohesionMod = 1.0;
double separationMod = 1.0;
double scale = 70;

double fps_cap = 60;

const int threadCount = 32;
const int boidPerThread = (int)boidQty / (int)threadCount;
const int leftoverBoids = boidQty % threadCount;

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void UpdateBoids(std::vector<Boid>& refBoids, std::vector<Boid> boids, int startIndex, int endIndex) {
    for (int i = startIndex; i <= endIndex; i++) {
        refBoids[i].edges();
        refBoids[i].flock(boids);
        refBoids[i].update();
        refBoids[i].show();
    }
}

bool HandleInput() {
    // Handle Input
    char c = getch();
    if (c == 'q' || c == 'Q') {
        return false;
    }

    switch (c) {
        case 'y': // Increase align
            alignMod += 0.1;
            break;
        case 'h': // Decrease align
            alignMod -= 0.1;
            break;
        case 'u': // Increase cohesion
            cohesionMod += 0.1;
            break;
        case 'j': // Decrease cohesion
            cohesionMod -= 0.1;
            break;
        case 'i': // Increase separation
            separationMod += 0.1;
            break;
        case 'k': // Decrease separation
            separationMod -= 0.1;
            break;
        case 'w': // Increase scale
            scale += 10;
            break;
        case 's': // Decrease scale
            scale -= 10;
            break;
        case 'e': // Increase max force
            maxForce += 0.1;
            break;
        case 'd': // Decrease max force
            maxForce -= 0.1;
            break;
        case 'r': // Increase max speed
            maxSpeed += 1.0;
            break;
        case 'f': // Decrease max speed
            maxSpeed -= 1.0;
            break;
        case 't': // Increase perception
            perception += 10;
            break;
        case 'g': // Decrease perception
            perception -= 10;
            break;
    }

    return true;
}

int main() {
    srand(time(NULL));

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    curs_set(0);

    // Set up the boid counts for each thread to process
    int threadBoidCapacity[threadCount];
    for (int i = 0; i < threadCount; i++) {
        threadBoidCapacity[i] = boidPerThread;
    }

    for (int i = 0; i < leftoverBoids; i++) {
        threadBoidCapacity[i]++;
    }

    // Add one to the last group, since the later loop is exclusive and will miss the last boid otherwise
    threadBoidCapacity[threadCount - 1]++;

    // Create the boids at random places with random starting velocities
    std::vector<Boid> boids;
    for (int i = 0; i < boidQty; i++) {
        boids.push_back(Boid(RandomFloat(0, COLS * scale), RandomFloat(0, LINES * scale), 0, 0));
    }

    while (HandleInput()) {
        auto timeOverallStart = std::chrono::high_resolution_clock::now();

        clear();

        std::vector<std::thread> threads;
        int curIndex = 0;
        for (int i = 0; i < threadCount; i++) {
            threads.push_back(std::thread(UpdateBoids, std::ref(boids), boids, curIndex, threadBoidCapacity[i] + curIndex - 1));
            curIndex += threadBoidCapacity[i];
        }

        for (auto& t : threads) {
            t.join();
        }

        // Draw the current modifiers
        mvprintw(0, 0, "[+Y-H] Alignment Mod:  %f", alignMod);
        mvprintw(1, 0, "[+U-J] Cohesion Mod:   %f", cohesionMod);
        mvprintw(2, 0, "[+I-K] Separation Mod: %f", separationMod);
        
        // Draw the boid info
        mvprintw(4, 0, "[+W-S] Scale:      %f", scale);
        mvprintw(5, 0, "[+E-D] Max Force:  %f", maxForce);
        mvprintw(6, 0, "[+R-F] Max Speed:  %f", maxSpeed);
        mvprintw(7, 0, "[+T-G] Perception: %f", perception);

        refresh();

        auto timeOverallEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> timeOverallElapsed = timeOverallEnd - timeOverallStart;

        double leftoverTime = (1000.0 / fps_cap) - timeOverallElapsed.count();
        std::this_thread::sleep_for(std::chrono::milliseconds((long)leftoverTime));
    }

    refresh();
    getch();
    endwin();

    return 0;
}
