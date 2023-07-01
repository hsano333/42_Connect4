#ifndef RENDER_H
#define RENDER_H
#include "board.h"
#include <stdbool.h>

#define BS 8
#define LEFT_KEY 104
#define RIGHT_KEY 108
#define ENTER_KEY1 10
#define ENTER_KEY2 13
#define LEFT_ARRAY_KEY 4479771
#define RIGHT_ARRAY_KEY 4414235
#define CR 13

bool init_ncurses();
void render(t_board *board);
void render_input(t_board *board, int x);
void render_clear();
void end_ncurses();
void render_player(t_board *board, int pre_x);


#endif
