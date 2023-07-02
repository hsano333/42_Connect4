#include "ai_bonus.h"
#include "render.h"
#include <ncurses.h>

char evaluation_score(t_board *board)
{
    (void)board;
    int y = 0;
    t_point *point;
    int ai_score = 0;
    int player_score = 0;
    for(int x=0;x<board->col_max;x++){
        y = board->pos_x[x]-1;
        if(y < 0 || y >= board->row_max){
            continue;
        }
        point = &(board->board[y][x].point);
        if(board->board[y][x].color == RED){
            ai_score += point->vertical * 25;
            ai_score += point->horizontal * 25;
            ai_score += point->right_diagonal * 25;
            ai_score += point->left_diagonal * 25;
        }else if(board->board[y][x].color == YELLOW){
            player_score += point->vertical * 25;
            player_score += point->horizontal * 25;
            player_score += point->right_diagonal * 25;
            player_score += point->left_diagonal * 25;
        }
    }
    int diff = ((ai_score - player_score)*2) / board->col_max;
    return (diff);
}

 #include <unistd.h>
char evaluation(t_board *board, int x1, int cnt)
{
    static int count = 0;
    count++;
    char rate[board->col_max];
    bool ng_flag = false;
    int y1,y2;
    bool exit = false;

    cnt--;

        y1 = board->pos_x[x1];

        if(insert_board(board, x1, RED, &exit, true)){
            refresh();
            return (100);
        }
            refresh();
        if(!exit){
            return (-100);
        }

        if(cnt < 0){
            char tmp = evaluation_score(board);
            return (tmp);
        }

        for(int x2=0; x2 < board->col_max;x2++){
            y2 = board->pos_x[x2];

            if(insert_board(board, x2, YELLOW, &exit, true)){
                ng_flag = true;
                rate[x2] = -100;
                break;
            }
            refresh();
            if(!exit){
            refresh();
                rate[x2] = 0;
            refresh();
            refresh();
                continue;
            }
            refresh();
            for(int x3=0; x3 < board->col_max;x3++){

                t_board tmp;
                t_board *ai_board = copy_board(&tmp, board);
                refresh();
                if(ai_board != NULL){
                    rate[x2] = evaluation(ai_board, x3, cnt) * 0.9;
                    clear_board(ai_board);
                }else{
                    rate[x2] = 0;
                }
            }
        }
        refresh();
        refresh();
    if (ng_flag){
        return (-100);
    }
    int sum = 0;
    for(int i=0;i<board->col_max;i++){
        sum += rate[i];
    }
    sum = sum / board->col_max;
    return (sum);

}


int ai_bonus(t_board *board)
{
    char rate[board->col_max];
    int cnt = 75 / board->col_max;
    if(cnt >= 2){
        cnt = 2;
    }
    if (cnt < 1){
        cnt = 0;
    }

    for(int x=0; x < board->col_max;x++){

        t_board tmp;
        t_board *ai_board = copy_board(&tmp, board);
                refresh();

        rate[x] = evaluation(ai_board, x, cnt);
        clear_board(ai_board);
    }



    (void)board;
    char max = 0;
    int return_x = 0;
    bool check = false;
    for(int i=0;i<board->col_max;i++){
        if(max <= rate[i]){
            check = true;
            max = rate[i];
            return_x = i;
        }
    }
    if (check){

    }

    return (return_x);
}
