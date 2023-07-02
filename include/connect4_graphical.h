#ifndef CONNECT4_GRAPHICAL_H
#define CONNECT4_GRAPHICAL_H

#include <stdbool.h>

#define WIN 4

#define BLANK 0     
#define PLAYER 1    
#define AI 2  

bool connect4_graphical(int x, int y);

typedef enum E_TURN
{
    TURN_AI,
    TURN_PLAYER,
}TURN;

typedef enum E_COLOR
{
    BLACK = 0,
    DEFAULT = 1,
    YELLOW = 2,
    RED = 3,
    GREEN = 5,
    MAGENTA = 6,
    CYAN = 7,

} COLOR;

#endif
