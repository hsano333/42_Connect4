#include "connect4_graphical.h"
#include "board.h"
#include "render.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

static bool init(t_board *board, int col_max, int row_max)
{
    srand(time(NULL));
    if(!init_board(board,col_max, row_max)){
        return (false);
    }

    if(!init_ncurses()){
        return (false);
    }
    return (true);
}

static size_t ai_test(char **board, int user_x, int max_x, int max_y)
{
    (void)board;
    (void)user_x;
    (void)max_x;
    (void)max_y;
    return (((size_t)rand()) % max_x);
}

static size_t random_ai(int col)
{
    return (((size_t)rand()) % col);
}

static int player_turn(t_board *board)
{
    int c;
    int x=0;
	while (1){
        render_clear();
        render_player(board,x);
        c = 0;
        int size=read(0, &c, 4);
        refresh();
        if ((c == LEFT_KEY && size==1) || (c == LEFT_ARRAY_KEY && size==3)){
            if(x > 0){
                x--;
            }
        }else if ((c == RIGHT_KEY && size==1) || (c == RIGHT_ARRAY_KEY && size==3)){
            if(x < board->col_max-1){
                x++;
            }
        }else if ((c == ENTER_KEY1 || (c == ENTER_KEY2)) && size==1){
            break;
        }
    }

    return (x);
}

bool connect4_graphical(int max_col, int max_row)
{
    int who_win = -1;
    t_board board;
    if(!init(&board, max_col, max_row)){
        return (false);
    }

    TURN turn = (((int)rand())) % 2;
    while(!check_end_game(&board))
    {
        render_clear();
        render(&board);
        int x = -1;
        int user_x = -1;
        bool exit = false;
        if (turn == TURN_AI){
            while(!exit){
                x = ai_test(board.boardX, user_x, board.col_max, board.row_max);
                x = random_ai( (board.col_max));
                if(insert_board(&board, x, RED, &exit)){
                    who_win = AI;
                }
            }
            turn = TURN_PLAYER;
        }else{
            while(!exit){
                x = player_turn(&board);
                user_x = x;
                if(insert_board(&board, x, YELLOW, &exit)){
                    who_win = PLAYER;
                }
            }
            turn = TURN_AI;
        }
        refresh();
        render_input(&board, x);
        if (who_win != -1){
            break;
        }
    }
    render_clear();
    render(&board);
    if (who_win == -1){
        printw("Draw\n");
    }else if (who_win == AI){
        printw("AI Win\n");
    }else if (who_win == PLAYER){
        printw("PLAYER Win\n");
    }
    printw("End\n");
    refresh();
    sleep(3);
    clear_board(&board);
    end_ncurses();
        
    return (true);
}
