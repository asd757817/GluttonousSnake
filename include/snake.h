#include "env.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

struct snake_node_t {
    int x;
    int y;

    struct snake_node_t *prev;
    struct snake_node_t *next;
};

struct snake_t {
    struct snake_node_t *head;
    struct snake_node_t *tail;
    int direction;
    int length;
};

struct snake_t g_snake;

void snake_init();
void snake_move(int direction);
void snake_keep_run();
