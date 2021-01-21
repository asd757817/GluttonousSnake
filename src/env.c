#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "../include/env.h"


void map_init() {
    int x, y;
    for (y = 0; y < Y_FIELD; y++) {
        for (x = 0; x < X_FIELD; x++) {
            if (y == 0 || x == 0 || y == Y_FIELD - 1 || x == X_FIELD - 1) {
                g_map[y][x] = WALL;
            } else {
                g_map[y][x] = ROAD;
            }
        }
    }
}

void generate_point(void) {
    int point_x;
    int point_y;

    do {
        point_x = 1 + rand() % (X_FIELD - 1);
        point_y = 1 + rand() % (Y_FIELD - 1);
    } while (g_map[point_y][point_x] != ROAD);
    g_map[point_y][point_x] = POINT;

    return;
}

void display_screen() {
    int x, y;
    for (y = 0; y < Y_FIELD; y++) {
        for (x = 0; x < X_FIELD; x++) {
            switch (g_map[y][x]) {
            case WALL:
                printw("X");
                break;
            case ROAD:
                printw(" ");
                break;
            case HEAD:
                printw("O");
                break;
            case BODY:
                printw("#");
                break;
            case POINT:
                printw("*");
                break;
            default:
                printw(" ");
                break;
            }
        }
        printw("\n");
    }
}

void *getkeystroke() {
    while (!g_gameover) {
        g_keystroke = getch();
    }
    return NULL;
}
