#include <ncurses.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define X_field 80
#define Y_field 40

/* Variables for whole game */
bool gameover = false;
int keystroke, point_x, point_y, scores = 0, speed = 1;
int map[Y_field + 1][X_field + 1];
int target = 500;

/* Variables for snake control*/
int snake_length = 4;
int next_direction = 4; /* up:1, down:2, left:3, right:4 */
typedef struct snake_t {
    int x, y;
    int direction;
    struct snake_t *next, *prev;
} snake_t;
snake_t *snake_head, *snake_tail;

/* Add new nodes to snake */
static int snake_add2head(snake_t *new_node) {
    if (!new_node)
        return -1;
    else {
        new_node->next = snake_head;
        snake_head->prev = new_node;
        snake_head = new_node;

        return 0;
    }
}
static int snake_add2tail(snake_t *new_node) {
    if (!new_node)
        return -1;
    else {
        snake_tail->next = new_node;
        new_node->prev = snake_tail;
        snake_tail = new_node;
    }
}

/* Generate point randomly */
static void generate_point(void) {
    do {
        point_x = 1 + rand() % (X_field - 1);
        point_y = 1 + rand() % (Y_field - 1);
    } while (map[point_y][point_x] != 0);
    map[point_y][point_x] = 100;
    return;
}

/* Update location of snake. */
static void snake_move() {
    snake_t *new_node = malloc(sizeof(struct snake_t));
    next_direction = snake_head->direction;
    bool remove_tail = true;

    switch (keystroke) {
        case KEY_UP:
            next_direction = 1;
            break;
        case KEY_DOWN:
            next_direction = 2;
            break;
        case KEY_LEFT:
            next_direction = 3;
            break;
        case KEY_RIGHT:
            next_direction = 4;
            break;
    }

    switch (next_direction) {
        case 1:
            new_node->y = snake_head->y - 1;
            new_node->x = snake_head->x;
            break;
        case 2:
            new_node->y = snake_head->y + 1;
            new_node->x = snake_head->x;
            break;
        case 3:
            new_node->x = snake_head->x - 1;
            new_node->y = snake_head->y;
            break;
        case 4:
            new_node->x = snake_head->x + 1;
            new_node->y = snake_head->y;
            break;
    }

    /* Get point */
    if (map[new_node->y][new_node->x] == 100) {
        scores += speed;
        if (scores < 2)
            speed = 1;
        else if (scores < 5)
            speed = 2;
        else if (scores < 10)
            speed = 3;
        else if (scores < 15)
            speed = 4;
        else
            speed = 5;
        generate_point();
        remove_tail = false;
        snake_length += 1;
    } else if (map[new_node->y][new_node->x] != 0) {
        gameover = true;
        clear();
        if (scores > target)
            printw("You WIN!!!\n");
        else
            printw("GAME OVER!\n");

        refresh();
        return;
    }

    /* Update direction of head_node */
    new_node->direction = next_direction;
    map[snake_head->y][snake_head->x] = 2;
    snake_add2head(new_node);
    map[snake_head->y][snake_head->x] = 3;

    /* Remove tail */
    if (remove_tail) {
        map[snake_tail->y][snake_tail->x] = 0;
        snake_tail = snake_tail->prev;
        snake_tail->next = NULL;
    }
}

/* Get user keystroke */
static void *getkeystroke() {
    while (!gameover) {
        keystroke = getch();
    }
    return NULL;
}

/* Display  */
static void display_screen() {
    /* map */
    for (int i = 0; i <= Y_field; i++) {
        for (int j = 0; j <= X_field; j++) {
            if (map[i][j] == 1)
                printw("X");
            else if (map[i][j] == 0)
                printw(" ");
            else if (map[i][j] == 2)
                printw("#");
            else if (map[i][j] == 3)
                printw("O");
            else if (map[i][j] == 100)
                printw("*");
        }
        printw("\n");
    }

    /* Game info */
    printw("\n\n");
    printw("Use UP, DOWN, LEFT and RIGHT to control you worm.\n\n");
    printw("You will see the Flag when your scores reach 500 points.\n\n");
    printw("Scores: %d \t\t Speed_Level: %d\n", scores, speed);

    return;
}

static void map_init() {
    for (int i = 0; i <= Y_field; i++) {
        for (int j = 0; j <= X_field; j++)
            if ((i == 0 || i == Y_field) || (j == 0 || j == X_field))
                map[i][j] = 1;
            else
                map[i][j] = 0;
    }
}

static void snake_init() {
    snake_head = malloc(sizeof(struct snake_t));
    snake_head->x = 6, snake_head->y = 6;    // Snake head is at (6,6).
    snake_head->direction = next_direction;  // Default direction is RIGHT
    snake_head->next = NULL, snake_head->prev = NULL, snake_tail = snake_head;
    map[snake_head->y][snake_head->x] = 3;  // Set snake head on the map.

    /* Add snake body */
    for (int i = 1; i < snake_length; i++) {
        snake_t *tmp = malloc(sizeof(struct snake_t));
        tmp->x = 6 - i;
        tmp->y = 6;
        tmp->direction = next_direction;
        map[tmp->y][tmp->x] = 2;
        snake_add2tail(tmp);
    }
}

int main() {
    srand(time(NULL));

    /* ncurses_init */
    WINDOW *win;
    win = initscr();
    cbreak();
    noecho();
    keypad(win, 1);

    /* Initialize map */
    map_init();
    /* Snake initialization */
    snake_init();
    /* Initialize point */
    generate_point();

    /* Use a thread to recieve user keystroke */
    pthread_t p_GetKeystroke;
    pthread_create(&p_GetKeystroke, NULL, getkeystroke, NULL);

    while (!gameover) {
        clear();
        display_screen();
        refresh();
        snake_move(snake_head, snake_tail);
        usleep(550000 - speed * 100000);
    }
    pthread_join(p_GetKeystroke, NULL);

    return 0;
}
