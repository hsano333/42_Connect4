#ifndef CONNECT4_GRAPHICAL_H
#define CONNECT4_GRAPHICAL_H

#include <stdbool.h>

#define WIN 4

bool connect4_graphical(int x, int y);

typedef enum E_TURN
{
    AI,
    PLAYER,
}TURN;

typedef enum E_COLOR
{
    BLACK = 0,
    DEFAULT = 1,
    YELLOW = 2,
    RED = 3,
    GREEN = 5,
    CYAN = 7,

} COLOR;

#endif
