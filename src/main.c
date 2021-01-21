#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/env.h"
#include "../include/snake.h"

int g_gameover = 0;
int g_speed = 1;

int main() {
    srand(time(NULL));

    /* ncurses_init */
    WINDOW *win;
    win = initscr();
    cbreak();
    noecho();
    keypad(win, 1);

    map_init();
    snake_init();
    generate_point();

    /* Use a thread to recieve user keystroke */
    pthread_t tid_GetKeystroke;
    pthread_create(&tid_GetKeystroke, NULL, getkeystroke, NULL);

    while (!g_gameover) {
        clear();
        display_screen();
        refresh();
        snake_keep_run(g_snake.direction);
        sleep(1);
    }
    pthread_join(tid_GetKeystroke, NULL);

    return 0;
}
