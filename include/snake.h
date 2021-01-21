#include <env.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

struct snake_node_t{
    int x;
    int y;
};

struct snake_t {
    struct snake_t *head;
    struct snake_t *tail;
    int direction;
    int length;
};

int snake_move(struct snake_t *snake, int direction);
