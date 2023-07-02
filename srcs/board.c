#include "board.h"
#include "libft.h"
#include "render.h"
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

bool init_board(t_board *board, int col_max, int row_max)
{
    board->col_max = col_max;
    board->row_max = row_max;

    board->mem = (t_mass *)ft_calloc(sizeof(t_mass) , col_max * row_max);
    if (!board->mem){
        return (false);
    }
    board->memX = (char *)ft_calloc(sizeof(char) , col_max * row_max);
    if (!board->memX){
        free(board->mem);
        return (false);
    }

    for(int y = 0; y < row_max; y++){
        board->board[y] = &(board->mem[y * col_max]);
        board->boardX[y] = &(board->memX[y * col_max]);
    }
    ft_memset(board->pos_x,0, GRID_MAX);
    return (true);
}

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

static bool check_win(t_board *board, COLOR color, int x, int y, bool dont_change)
{
    //return (false);
    int left = 0;
    int right = 0;
    //int up = 0;
    int down = 0;
    int up_left = 0;
    int up_right = 0;
    int down_left = 0;
    int down_right = 0;

    if (x < 0 || x >= board->col_max || y < 0 || y >= board->row_max){
        return (false);
    }

    t_point *point = &(board->board[y][x].point);
    if(x > 0){
        left = (board->board[y][x-1].color == color) ?  board->board[y][x-1].point.horizontal : 0;
        if(y > 0 && board->board[y-1][x-1].color == color){
            down_left = board->board[y-1][x-1].point.right_diagonal;
        }
        if(y < board->row_max -1 && board->board[y+1][x-1].color == color){
            up_left = board->board[y+1][x-1].point.left_diagonal;
        }
    }
    if(x < board->col_max -1){
        right = board->board[y][x+1].color == color ?  board->board[y][x+1].point.horizontal : 0;
        if(y > 0 && board->board[y-1][x+1].color == color){
            down_right = board->board[y-1][x+1].point.left_diagonal;
        }
        if(y < board->row_max -1 && board->board[y+1][x+1].color == color){
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

    if (!dont_change){
        for(int i=1;i<=left;i++){
            board->board[y][x-i].point.horizontal = point->horizontal;
            if (point->horizontal >= WIN){
                board->board[y][x-i].win = true;
            }
        }
        for(int i=1;i<=right;i++){
            board->board[y][x+i].point.horizontal = point->horizontal;
            if (point->horizontal >= WIN){
                board->board[y][x+i].win = true;
            }
        }
        for(int i=1;i<=down;i++){
            board->board[y-i][x].point.vertical = point->vertical;
            if (point->vertical >= WIN){
                board->board[y-i][x].win = true;
            }
        }

        for(int i=1;i<=up_left;i++){
            board->board[y+i][x-i].point.left_diagonal = point->left_diagonal;
            if (point->left_diagonal >= WIN){
                board->board[y+i][x-i].win = true;
            }
        }
        for(int i=1;i<=up_right;i++){
            board->board[y+i][x+i].point.right_diagonal = point->right_diagonal;
            if (point->right_diagonal >= WIN){
                board->board[y+i][x+i].win = true;
            }
        }
        for(int i=1;i<=down_left;i++){
            board->board[y-i][x-i].point.right_diagonal = point->right_diagonal;
            if (point->right_diagonal >= WIN){
                board->board[y-i][x-i].win = true;
            }
        }
        for(int i=1;i<=down_right;i++){
            board->board[y-i][x+i].point.left_diagonal = point->left_diagonal;
            if (point->left_diagonal >= WIN){
                board->board[y-i][x+i].win = true;
            }
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




bool insert_board(t_board *board, int x, COLOR color, bool *is_continue, bool dont_change)
{
    if (0 <= x && x < board->col_max)
    {
        int y = board->pos_x[x];
        if (0 <= y && y < board->row_max){
            board->board[y][x].color = color;
            board->boardX[y][x] = (color == RED) ? AI : PLAYER;
            board->pos_x[x]++;
            //if(board->pos_x[x] >= board->row_max){
                //board->pos_x[x] = board->row_max-1;
            //}

            *is_continue = true;
            return (check_win(board,color, x, y, dont_change));
        }
    }
    *is_continue = false;
    return (false);
}

void reverse_board(t_board *board, int x, int y, t_point *mass)
{
    return ;
    (void)board;
    (void)x;
    (void)y;
    //printw("x=%d, y=%d, test=%d\n", x, y,test);
    board->board[y][x].color = BLACK;
    board->board[y][x].win = false;

    board->boardX[y][x] = BLACK;
    board->board[y][x].point = *mass;
    //if(x > 1 && x < 5 && y>1 && y< 5){
        //board->pos_x[x] = y;
        board->pos_x[x]--;
        if (board->pos_x[x] < 0){
            board->pos_x[x] = 0;
        }

    //}
    //printw("end\n", x, y);
}


t_board *copy_board(t_board *dst, t_board *src)
{
            //return (NULL);

    //t_board *cp;

    //cp->mem = 
    dst->mem = (t_mass *)ft_calloc(sizeof(t_mass) ,src->col_max * src->row_max);
    if (!dst->mem){
        return (NULL);
    }
    dst->memX = (char *)ft_calloc(sizeof(char) , src->col_max * src->row_max);
    if(!dst->memX){
        free(dst->mem);
        return (NULL);
    }
    for(int y = 0; y < src->row_max; y++){
        dst->board[y] = &(dst->mem[y * src->col_max]);
        dst->boardX[y] = &(dst->memX[y * src->col_max]);
    }

    ft_memcpy(dst->mem, src->mem, sizeof(t_mass) * src->col_max * src->row_max);
    ft_memcpy(dst->memX, src->memX, sizeof(char) * src->col_max * src->row_max);
    ft_memcpy(dst->pos_x, src->pos_x, sizeof(int) * GRID_MAX);
    dst->end = src->end;
    dst->col_max = src->col_max;
    dst->row_max = src->row_max;

    return (dst);
}

void clear_board(t_board *board)
{
    free(board->mem);
    free(board->memX);
}
