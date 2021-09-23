#include <curses.h>
#include <stdlib.h>

#include "Headers/vec.h"

int sign(int x) {
    return (x > 0) - (x < 0);
}

struct Vec {
    int x;
    int y;
};

void BresenhamLine(int x1, int y1, int x2, int y2) {
    int rise = y2 - y1;
    int run = x2 - x1;
    int slope = rise / run;
}

void testDrawLine(int x1, int y1, int x2, int y2) {
    const int dX = x2 - x1;
    const int dY = y2 - y1;
    const int absDX = abs(dX);
    const int absDY = abs(dY);

    int x = x1;
    int y = y1;
    mvaddch(y, x, '#');

    if (absDX > absDY) {
        int d = 2 * absDY - absDX;
        for (int i = 0; i < absDX; i++) {
            x = dX < 0 ? x - 1 : x + 1;
            if (d < 0) {
                d = d + 2 * absDY;
            } else {
                y = dY < 0 ? y - 1 : y + 1;
                d = d + (2 * absDY - 2 * absDX);
            }
            mvaddch(y, x, '#');
        }
    } else {
        int d = 2 * absDX - absDY;
        for (int i = 0; i < absDY; i++) {
            y = dY < 0 ? y - 1 : y + 1;
            if (d < 0) {
                d = d + 2 * absDX;
            } else {
                x = dX < 0 ? x - 1 : x + 1;
                d = d + (2 * absDX - 2 * absDY);
            }
            mvaddch(y, x, '#');
        }
    }
}

void drawline(Vec p1, Vec p2) {
    int deltaX = p2.x - p1.x;
    int deltaY = p2.y - p1.y;

    p2.x += sign(deltaX);
    p2.y += sign(deltaY);

    int A, B, P, lineDirection;
    if (abs(deltaY) > abs(deltaX)) {
        A = 2 * abs(deltaX);
        B = A - (abs(2 * deltaY));
        P = A - abs(deltaY);
        lineDirection = deltaY > 0 ? 1 : -1;
    } else if (abs(deltaX) == abs(deltaY)) {
        A = 2 * abs(deltaY);
        B = A - (abs(2 * deltaX));
        P = A - abs(deltaX);
        lineDirection = sign(deltaY);
    } else {
        A = 2 * abs(deltaY);
        B = A - (abs(2 * deltaX));
        P = A - abs(deltaX);
        lineDirection = deltaX > 0 ? 1 : -1;
    }

    mvaddch(p1.y, p1.x, '#');

    if (abs(deltaY) > abs(deltaX)) {
        int curX = p1.x;
        for (int curY = p1.y; curY != p2.y; curY += sign(deltaY)) {
            if (P < 0) {
                mvaddch(curY, curX, '#');
                P += A;
            } else {
                curX += lineDirection;
                mvaddch(curY, curX, '#');
                P += B;
            }
        }
    } else {
        int curY = p1.y;
        for (int curX = p1.x; curX != p2.x; curX += sign(deltaX)) {
            if (P < 0) {
                mvaddch(curY, curX, '#');
                P += A;
            } else {
                curY += lineDirection;
                mvaddch(curY, curX, '#');
                P += B;
            }
        }
    }
}

int main() {
    initscr();

    Vec p1 = { .x = 5, .y = 0 };
    Vec p2 = { .x = 10, .y = 5 };
    Vec p3 = { .x = 5, .y = 10 };
    Vec p4 = { .x = 0, .y = 5 };

    testDrawLine(p1.x, p1.y, p2.x, p2.y);
    getch();
    testDrawLine(p2.x, p2.y, p3.x, p3.y);
    getch();
    testDrawLine(p3.x, p3.y, p4.x, p4.y);
    getch();
    testDrawLine(p4.x, p4.y, p1.x, p1.y);
    getch();

    vec2d newvec(10, 5);
    mvaddstr(1, 1, newvec.toString().c_str());

    refresh();
    getch();
    endwin();

    return 0;
}
