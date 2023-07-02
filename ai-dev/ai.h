#ifndef AI_H
# define AI_H

#define UNPLACED '\0'
#define RED 'r'
#define YELLOW 'y'

// #define is_inboard(x, y, max_x, max_y) (0 <= (x) && (x) < (max_x) && 0 <= (y) && (y) < (max_y))

int ai(char **board, int player_put_x, int width, int height);

#endif
