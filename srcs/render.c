#include "render.h"
#include <ncurses.h>

void	init_color_pair(void)
{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_pair(8, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(9, COLOR_GREEN, COLOR_MAGENTA);
	init_pair(10, COLOR_BLUE, COLOR_GREEN);
	init_pair(11, COLOR_RED, COLOR_BLUE);
	init_pair(12, COLOR_YELLOW, COLOR_RED);
	init_pair(13, COLOR_RED, COLOR_GREEN);
	init_pair(14, COLOR_RED, COLOR_CYAN);
	init_pair(15, COLOR_BLUE, COLOR_WHITE);
	init_pair(16, COLOR_BLACK, COLOR_YELLOW);
	init_pair(17, COLOR_BLACK + 8, COLOR_WHITE);
	init_pair(18, COLOR_BLACK, COLOR_BLACK);
}



bool init_ncurses()
{
    if (!initscr()){
        return (false);
    }
    init_color_pair();
    refresh();
    return (true);
}

void render(t_board *board)
{
    attron(COLOR_PAIR(DEFAULT));
    printw("+");
    for(int i=0;i<board->col_max;i++){
        printw("--");
    }
    for(int y=board->row_max-1; y>= 0; y--)
    {
        printw("%c+\n|", BS);
        for(int x=0;x<board->col_max;x++){
            COLOR color = get_color(board, x, y);
            attron(COLOR_PAIR(color));
            printw("O");
            attron(COLOR_PAIR(DEFAULT));
            printw("|");
        }
        printw("\n");
        printw("+");
        for(int i=0;i<board->col_max;i++){
            printw("-+");
        }
    }
    printw("\n");
    refresh();
}

void render_player(t_board *board, int pre_x)
{
    int pre_y = board->pos_x[pre_x];
    attron(COLOR_PAIR(DEFAULT));
    printw("+");
    for(int i=0;i<board->col_max;i++){
        printw("--");
    }
    for(int y=board->row_max-1; y>= 0; y--)
    {
        printw("%c+\n|", BS);
        for(int x=0;x<board->col_max;x++){
            COLOR color = get_color(board, x, y);
            if (x == pre_x && y == pre_y){
                color = CYAN;
            }
            attron(COLOR_PAIR(color));
            printw("O");
            attron(COLOR_PAIR(DEFAULT));
            printw("|");
        }
        printw("\n");
        printw("+");
        for(int i=0;i<board->col_max;i++){
            printw("-+");
        }
    }
    printw("\n");
    refresh();
}

void render_input(t_board *board, int x)
{
    (void)board;
    (void)x;

}
void render_clear()
{
    clear();
}

void end_ncurses()
{
    endwin();
}
