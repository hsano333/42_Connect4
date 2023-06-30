#include "board.h"
#include "libft.h"
#include <stdlib.h>


#include <stdio.h>
bool init_board(t_board *board, int col_max, int row_max)
{
    board->col_max = col_max;
    board->row_max = row_max;

    board->base = (char *)ft_calloc(col_max , row_max);
    if (!board->base){
        return (false);
    }
    for(int y = 0; y < row_max; y++){
        board->board[y] = &(board->base[y * col_max]);
    }

    /* for test
    for(int i=0;i< (col_max*row_max);i++){
        board->base[i] = i;
        printf("board->base[%d]=%d, p=%p\n",i, board->base[i], &board->base[i] );
    }
    printf("-------------------------------\n");
    for(int y = 0; y < row_max; y++){
        for(int x = 0; x < col_max; x++){
            printf("x=%d,y=%d\n", x,y);
            printf("board->board[%d][%d]=%d, p=%p\n", y, x, board->board[y][x],&board->board[y][x] );
            //board->board[y] = &(board->base[y*col_max]);
        }
    }
    */
    return (true);
}

void set_border()
{

}
