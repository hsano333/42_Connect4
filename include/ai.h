#ifndef AI_H
# define AI_H

#define BLANK 0
#define PLAYER 1
#define AI 2

#define UNPLACED BLANK
//#define RED PLAYER
//#define YELLOW AI

#include <stdbool.h>


void set_board(char ***board, int put_x, int height, char turn);
bool is_win(char **board, int point_x, int point_y, int width, int height);
int ai(char **board, int player_put_x, int width, int height);

#endif
