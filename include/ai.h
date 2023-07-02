#ifndef AI_H
# define AI_H

#define BLANK 0
#define PLAYER 1
#define AI 2

#define UNPLACED BLANK
#define RED PLAYER
#define YELLOW AI


void set_board(char ***board, int put_x, int width, int height, char turn);
int ai(char **board, int player_put_x, int width, int height);

#endif