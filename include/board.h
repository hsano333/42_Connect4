#ifndef BORDER_H
#define BORDER_H

#include "connect4.h"
#include "connect4_graphical.h"
# include <stdbool.h>

typedef struct s_point
{
    int vertical;
    int horizontal;
    int right_diagonal;
    int left_diagonal;
} t_point;

typedef struct s_mass
{
    bool win;
    t_point point;
    COLOR   color;
} t_mass;

typedef struct s_board
{
    bool end;
    int col_max;
    int row_max;
    //int tmp[30];
    t_mass *mem;
    t_mass *board[GRID_MAX];
    char *memX;
    char *boardX[GRID_MAX];
    int pos_x[GRID_MAX];
} t_board;

bool init_board(t_board *board, int col_max, int row_max);
bool check_end_game(t_board *board);
void clear_board(t_board *board);
bool insert_board(t_board *board, int x,  COLOR color, bool* is_continue, bool dont_change);
COLOR get_color(t_board *board, int x ,int y);
void reverse_board(t_board *board, int x, int y, t_point *test);
t_board *copy_board(t_board *dst, t_board *src);

#endif
