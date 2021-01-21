#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/env.h"
#include "../include/snake.h"

int g_map[Y_FIELD][X_FIELD];
int g_keystroke;
int g_gameover;


static struct snake_node_t *snake_new_node() {
    struct snake_node_t *node = malloc(sizeof(struct snake_node_t));
    if (!node) {
        return NULL;
    }

    memset(node, 0, sizeof(struct snake_node_t));

    return node;
}

void snake_init() {
    struct snake_node_t *head = snake_new_node();
    struct snake_node_t *body = snake_new_node();

    head->x = X_FIELD / 2;
    head->y = Y_FIELD / 2 - 1;
    g_map[head->y][head->x] = HEAD;

    body->x = head->x + 1;
    body->y = head->y;
    g_map[body->y][body->x] = BODY;

    head->next = body;
    body->prev = head;

    g_snake.head = head;
    g_snake.tail = body;
    g_snake.direction = LEFT;
}

static int illegal_direction(int direction) {
    if (direction != UP && direction != DOWN && direction != LEFT &&
        direction != RIGHT) {
        return -1;
    }
    return 0;
}

static int get_point(struct snake_node_t *head) {
    if (g_map[head->y][head->x] == POINT) {
        return 1;
    }
    return 0;
}

static int snake_add_head(struct snake_t *snake,
                          struct snake_node_t *new_head) {
    struct snake_node_t *head = g_snake.head;

    g_map[new_head->y][new_head->x] = HEAD;
    g_map[head->y][head->x] = BODY;
    new_head->next = head;
    head->prev = new_head;
    snake->head = new_head;
    snake->length++;

    return 0;
}

static int snake_del_tail() {
    struct snake_node_t *tail = g_snake.tail;

    g_map[tail->y][tail->x] = ROAD;
    g_snake.tail = tail->prev;
    g_snake.tail->next = NULL;
    g_snake.length--;

    free(tail);

    return 0;
}

void snake_move(int direction) {

    struct snake_node_t *new_head;
    struct snake_node_t *head = g_snake.head;

    if (illegal_direction(direction)) {
        return;
    }

    new_head = snake_new_node();
    switch (direction) {
    case UP:
        new_head->x = head->x;
        new_head->y = head->y - 1;
        break;
    case DOWN:
        new_head->x = head->x;
        new_head->y = head->y + 1;
        break;
    case LEFT:
        new_head->x = head->x - 1;
        new_head->y = head->y;
        break;
    case RIGHT:
        new_head->x = head->x + 1;
        new_head->y = head->y;
        break;
    default:
        break;
    }

    /* printf("(%d, %d) ---> (%d, %d)\n", head->x, head->y, new_head->x,
     * new_head->y); */

    if (get_point(new_head)) {
        generate_point();
    } else {
        snake_del_tail(&g_snake);
    }

    g_snake.direction = direction;
    snake_add_head(&g_snake, new_head);

    return;
}

void snake_keep_run() {

    switch (g_keystroke) {
    case KEY_UP:
        snake_move(UP);
        break;
    case KEY_DOWN:
        snake_move(DOWN);
        break;
    case KEY_LEFT:
        snake_move(LEFT);
        break;
    case KEY_RIGHT:
        snake_move(RIGHT);
        break;
    default:
        snake_move(g_snake.direction);
        break;
    }

    return;
}

#endif
