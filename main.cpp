#include <curses.h>
#include <stdlib.h>
#include <math.h>

#include "Headers/vec.h"
#include "Headers/draw.h"

struct Vec {
    int x;
    int y;
};

int main() {
    initscr();

    Vec p1 = { .x = 5, .y = 0 };
    Vec p2 = { .x = 10, .y = 5 };
    Vec p3 = { .x = 5, .y = 10 };
    Vec p4 = { .x = 0, .y = 5 };

    /* DDALine(0, 0, 5, 5); */
    /* DDALine(7, 0, 7, 5); */
    /* DDALine(15, 0, 9, 0); */
    /* getch(); */

    Line(p1.x, p1.y, p2.x, p2.y);
    getch();
    Line(p2.x, p2.y, p3.x, p3.y);
    getch();
    Line(p3.x, p3.y, p4.x, p4.y);
    getch();
    Line(p4.x, p4.y, p1.x, p1.y);
    getch();

    clear();
    Rect(2, 2, 10, 10);

    //vec2d newvec(10, 5);
    //mvaddstr(1, 1, newvec.toString().c_str());

    refresh();
    getch();
    endwin();

    return 0;
}
