#include "board.h"
#include "libft.h"
#include "render.h"
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

//static t_board board;

bool init_board(t_board *board, int col_max, int row_max)
{
    board->col_max = col_max;
    board->row_max = row_max;

    board->mem = (t_mass *)ft_calloc(sizeof(t_mass) , col_max * row_max);
    if (!board->mem){
        return (false);
    }
    for(int y = 0; y < row_max; y++){
        board->board[y] = &(board->mem[y * col_max]);
    }
    ft_memset(board->pos_x,0, col_max);

    return (true);
}

/*
bool init_board(t_board *board, int col_max, int row_max)
{
    board->col_max = col_max;
    board->row_max = row_max;

    board->mem = (char *)ft_calloc( col_max , row_max);
    if (!board->mem){
        return (false);
    }
    for(int y = 0; y < row_max; y++){
        board->board[y] = &(board->mem[y * col_max]);
    }
    ft_memset(board->pos_x, col_max, 0);

    return (true);
}
*/


COLOR get_color(t_board *board, int x, int y)
{
    if (board->board[y][x].win){
        return (GREEN);
    }
    if (board->board[y][x].color == BLACK){
        return (18);
    } else if (board->board[y][x].color == YELLOW){
        return (YELLOW);
    } else if (board->board[y][x].color == RED){
        return (RED);
    }
    return (DEFAULT);
}

void set_border()
{

}

static bool is_borad_full(t_board *board)
{
    (void)board;
    int y = board->row_max -1;
    bool is_full = true;
    for(int x=0;x<board->col_max; x++){
        if (board->board[y][x].color == BLACK){
            is_full = false;
            break;
        }
    }
    return (is_full);

}

bool check_end_game(t_board *board)
{
    (void)board;

    if (is_borad_full(board)){
        return (true);
    }


    return (false);
}

static bool check_win(t_board *board, COLOR color, int x, int y)
{
    int left = 0;
    int right = 0;
    //int up = 0;
    int down = 0;
    int up_left = 0;
    int up_right = 0;
    int down_left = 0;
    int down_right = 0;

    printw("x:%d, y:%d\n",x,y);
    t_point *point = &(board->board[y][x].point);
    //board->board[y][x].win = false;

    if(x > 0){
        left = (board->board[y][x-1].color == color) ?  board->board[y][x-1].point.horizontal : 0;
        if(y > 0 && board->board[y-1][x-1].color == color){
            down_left = board->board[y-1][x-1].point.right_diagonal;
        }
        if(y < board->col_max -1 && board->board[y+1][x-1].color == color){
            up_left = board->board[y+1][x-1].point.left_diagonal;
        }
    }
    if(x < board->col_max -1){
        right = board->board[y][x+1].color == color ?  board->board[y][x+1].point.horizontal : 0;
        if(y > 0 && board->board[y-1][x+1].color == color){
            down_right = board->board[y-1][x+1].point.left_diagonal;
        }
        if(y < board->col_max -1 && board->board[y+1][x+1].color == color){
            up_right = board->board[y+1][x+1].point.right_diagonal;
        }
    }
    if(y > 0 && board->board[y-1][x].color == color){
        down = board->board[y-1][x].point.vertical;
    }

    point->vertical = down + 1;
    point->horizontal = left + right + 1;
    point->right_diagonal = up_right + down_left + 1;
    point->left_diagonal = up_left + down_right + 1;
    printw("down:%d, left:%d,right=%d,up_right=%d,up_left=%d,down_left=%d,down_right=%d,down=%d\n",down,left,right,up_right,up_left,down_left,down_right, down);

    for(int i=1;i<=left;i++){
        board->board[y][x-i].point.horizontal = point->horizontal;
        if (point->horizontal >= WIN){
            board->board[y][x-i].win = true;
            printw("point->horizontal No.1:%d, color=%d\n", point->horizontal,board->board[y][x-i].color);
            printw("x:%d,y:%d,color=%d, left_diago:%d \n", x-i,y, board->board[y][x-i].color,board->board[y][x-i].point.left_diagonal);
        }
            if(color != board->board[y][x-i].color){
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");

            }
    }
    for(int i=1;i<=right;i++){
        board->board[y][x+i].point.horizontal = point->horizontal;
        if (point->horizontal >= WIN){
            board->board[y][x+i].win = true;
            printw("point->horizontal No.2:%d, color=%d\n", point->horizontal,board->board[y][x+i].color);
            printw("x:%d,y:%d,color=%d, left_diago:%d \n", x+i,y, board->board[y][x+i].color,board->board[y][x+i].point.left_diagonal);
        }
            if(color != board->board[y][x+i].color){
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");

            }
    }
    for(int i=1;i<=down;i++){
        board->board[y-i][x].point.vertical = point->vertical;
        if (point->vertical >= WIN){
            board->board[y-i][x].win = true;
            printw("point->vertical No.1:%d, color=%d\n", point->vertical,board->board[y-i][x].color);
            printw("x:%d,y:%d,color=%d, left_diago:%d \n", x,y-i, board->board[y-i][x].color,board->board[y-i][x].point.left_diagonal);
        }
            if(color != board->board[y-1][x].color){
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");

            }
    }

    for(int i=1;i<=up_left;i++){
        board->board[y+i][x-i].point.left_diagonal = point->left_diagonal;
        if (point->left_diagonal >= WIN){
            board->board[y+i][x-i].win = true;
            printw("point->left_diagonal No.1:%d, color=%d\n", point->left_diagonal,board->board[y+i][x-i].color);
            printw("x:%d,y:%d,color=%d, left_diago:%d \n", x+i,y-i, board->board[y+i][x-i].color,board->board[y+i][x-i].point.left_diagonal);
        }
            if(color != board->board[y+1][x-1].color){
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");

            }
    }
    for(int i=1;i<=up_right;i++){
        board->board[y+i][x+i].point.right_diagonal = point->right_diagonal;
        if (point->right_diagonal >= WIN){
            board->board[y+i][x+i].win = true;
            printw("point->right_diagonal No.1:%d, color=%d\n", point->right_diagonal,board->board[y+i][x+i].color);
            printw("x:%d,y:%d,color=%d, right_diago:%d \n", x+i,y+i, board->board[y+i][x+i].color,board->board[y+i][x+i].point.right_diagonal);
        }
            if(color != board->board[y+1][x+1].color){
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");

            }
    }
    for(int i=1;i<=down_left;i++){
        board->board[y-i][x-i].point.right_diagonal = point->right_diagonal;
        if (point->right_diagonal >= WIN){
            board->board[y-i][x-i].win = true;
            printw("point->right_diagonal No.2:%d, color=%d\n", point->right_diagonal,board->board[y-i][x-i].color);
            printw("x:%d,y:%d,color=%d, right_diago:%d \n", x-i,y-i, board->board[y-i][x-i].color,board->board[y-i][x-i].point.right_diagonal);
        }
            if(color != board->board[y-1][x-1].color){
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");

            }
    }
    for(int i=1;i<=down_right;i++){
        board->board[y-i][x+i].point.left_diagonal = point->left_diagonal;
        if (point->left_diagonal >= WIN){
            board->board[y-i][x+i].win = true;
            printw("point->left_diagonal No.2:%d, color=%d\n", point->left_diagonal,board->board[y-i][x+i].color);
            printw("x:%d,y:%d,color=%d, left_diago:%d \n", x-i,y+i, board->board[y-i][x+i].color,board->board[y-i][x+i].point.left_diagonal);
        }
            if(color != board->board[y-1][x+1].color){
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");
                printw("error!!!!!\n");

            }
    }

    if(point->horizontal >= WIN){
        board->board[y][x].win = true;
        return (true);
    }
    if(point->vertical >= WIN){
        board->board[y][x].win = true;
        return (true);
    }
    if(point->right_diagonal >= WIN){
        board->board[y][x].win = true;
        return (true);
    }
    if(point->left_diagonal >= WIN){
        board->board[y][x].win = true;
        return (true);
    }

    return (false);
}


bool insert_board(t_board *board, int x, COLOR color, bool *is_continue)
{
    if (0 <= x && x < board->col_max)
    {
        int y = board->pos_x[x];
        printw("insert_board x=%d, y=%d\n", x, y);
        if (0 <= y && y < board->row_max){
            board->board[y][x].color = color;
            board->pos_x[x]++;

            *is_continue = true;
            return (check_win(board,color, x, y));
        }
    }
    *is_continue = false;
    return (false);
}

void clear_board(t_board *board)
{
    free(board->mem);
}
