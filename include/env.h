#ifndef _ENV_H_
#define _ENV_H_

#define X_FIELD 80
#define Y_FIELD 60

extern int g_map[X_FIELD][Y_FIELD];
int g_point_x, g_point_y;
int g_speed = 1;
void generate_point(void);
#endif
