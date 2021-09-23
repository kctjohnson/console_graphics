#include <curses.h>
#include <math.h>
#include <algorithm>

#include "../Headers/draw.h"

void Point(int x, int y, char c) {
    mvaddch(y, x, c);
}

void Line(int x1, int y1, int x2, int y2) {
    BresenhamLine(x1, y1, x2, y2);
}

void Rect(int x, int y, int w, int h) {
    w--;
    h--;
    BresenhamLine(x, y, x + w, y);
    BresenhamLine(x + w, y, x + w, y + h);
    BresenhamLine(x + w, y + h, x, y + h);
    BresenhamLine(x, y + h, x, y);
}

// Based on https://medium.com/geekculture/dda-line-drawing-algorithm-be9f069921cf
void DDALine(int x1, int y1, int x2, int y2) {
    // Swap the start and end points if it's drawing from right to left
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    // Catch if the x values are the same, otherwise it causes divide by 0 error on slope
    // Vertical line
    if (dx == 0) {
        for (int i = 0; i <= dy; i++) {
            mvaddch(y1 + i, x1, '#');
        }
    } else {
        double slope = (double)dy / (double)dx;

        // Horizontal line
        if (slope == 0) {
            for (int x = x1; x <= x2; x++) {
                mvaddch(y1, x, '#');
            }
        } else if (slope == 1) { // Diagonal line
            for (int i = 0; i <= dx; i++) {
                mvaddch(y1 + i, x1 + i, '#');
            }
        } else { // Any other line
            for (int i = 0; i <= dx; i++) {
                int y = (int)round(((double)y1 + ((double)i * slope)));
                mvaddch(y, x1 + i, '#');
            }
        }
    }
}

// Code from https://medium.com/geekculture/bresenhams-line-drawing-algorithm-2e0e953901b3
void BresenhamLine(int x1, int y1, int x2, int y2) {
    const int dx = x2 - x1;
    const int dy = y2 - y1;
    const int absdx = abs(dx);
    const int absdy = abs(dy);

    int x = x1;
    int y = y1;
    mvaddch(y, x, '#');

    if (absdx > absdy) {
        int d = 2 * absdy - absdx;
        for (int i = 0; i < absdx; i++) {
            // Are we going up a slope or down a slope?
            x = dx < 0 ? x - 1 : x + 1;
            if (d < 0) {
                d = d + 2 * absdy;
            } else { // The decision variable has gone over 0, time to move along the y axis
                // Are we going up a slope or down a slope?
                y = dy < 0 ? y - 1 : y + 1;
                d = d + (2 * absdy - 2 * absdx);
            }
            mvaddch(y, x, '#');
        }
    } else {
        int d = 2 * absdx - absdy;
        for (int i = 0; i < absdy; i++) {
            // Are we going up a slope or down a slope?
            y = dy < 0 ? y - 1 : y + 1;
            if (d < 0) {
                d = d + 2 * absdx;
            } else { // The decision variable has gone over 0, time to move along the y axis
                // Are we going up a slope or down a slope?
                x = dx < 0 ? x - 1 : x + 1;
                d = d + (2 * absdx - 2 * absdy);
            }
            mvaddch(y, x, '#');
        }
    }
}
