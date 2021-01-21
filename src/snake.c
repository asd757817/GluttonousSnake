#include "snake.h"

struct snake_node_t *
snake_new_node(int direction)
{
	struct snake_node_t *node = malloc(sizeof(struct snake_node_t));
	if (!node)
	{
		return NULL;
	}

	memset(node, 0, sizeof(struct snake_node_t));

	return node;
}

static int
illegal_direction(int direction)
{
	if (direction != UP && direction != DOWN && direction != LEFT && direction != RIGHT)
	{
		return -1;
	}
	return 0;
}

static int
get_point(struct snake_t *snake)
{
    int i;
    for (i = 0;i < MAX_NUM_POINT;i++)
    {
        if (points[i]->x == snake->head->x && points[i]->y == snake->head->y)
        {
            return 1;
        }
    }
    return 0;
}

static int
snake_add_head(struct snake_t *snake, int direction)
{
	struct snake_t *head = snake->head;
	struct snake_t *new_head = snake_new_node();

	if (!snake || !new_head)
	{
		return -1;
	}

	switch (direction)
	{
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
	}
    
	new_head->next = head;
	snake->head = new_head;
    snake->direction = direction;
    snake->length++;

	return 0;
}

static int
snake_del_tail(struct snake_t *snake)
{
	struct *snake_node_t *old_tail = snake->tail;
	if (!snake)
	{
		return -1;
	}

	snake->tail = old_tail->prev;
	snake->tail->next = NULL;
    snake->length--;
	free(old_tail);

	return 0;
}

int snake_move(struct snake_t *snake, int direction)
{
	if (!snake || illegal_direction(direction))
	{
		return -1;
	}
    
    if (snake_add_head(snake, direction))
    {
        return -1;
    }

    if (!get_point(snake->head))
    {
        if (snake_del_tail(snake))
        {
            return -1;
        }
    }
    return 0;
}
