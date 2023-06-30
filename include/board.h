#ifndef BORDER_H
#define BORDER_H

#include "connect4.h"
# include <stdbool.h>

typedef struct s_board
{
    int col_max;
    int row_max;
    int tmp[30];
    char *base;
    char *board[GRID_MAX];
} t_board;

bool init_board(t_board *board, int col_max, int row_max);

#endif
