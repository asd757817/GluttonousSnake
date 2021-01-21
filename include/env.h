#ifndef _ENV_H_
#define _ENV_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>


#define X_FIELD 40
#define Y_FIELD 30

#define WALL -1
#define ROAD 0
#define HEAD 10
#define BODY 11
#define POINT 20

extern int g_map[Y_FIELD][X_FIELD];
extern int g_speed;
extern int g_keystroke;
extern int g_gameover;
extern int g_speed;

void map_init();
void generate_point();
void display_screen();
void *getkeystroke();

#endif
