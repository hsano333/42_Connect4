#include <stdio.h>
#include <stdlib.h>
#include "ai2.h"
#include "utils.h"

int main(int argc, char **argv) {
	int max_x = 7;
	int max_y = 6;
	char **board;
	board = calloc(max_y, sizeof(char *));
	for (int i = 0; i < max_y; i++) {
		board[i] = calloc(max_x, sizeof(char));
	}

	// char board[max_y][max_x];

    int ai_put;
    set_board(&board, 1, max_x, max_y, PLAYER);
    set_board(&board, 2, max_x, max_y, PLAYER);
    set_board(&board, 3, max_x, max_y, PLAYER);
    print_board(board, max_x, max_y);
    ai_put = ai(board, max_x / 2, max_x, max_y);
    set_board(&board, ai_put, max_x, max_y, AI);
    print_board(board, max_x, max_y);
    ai_put = ai(board, max_x / 2, max_x, max_y);
    set_board(&board, ai_put, max_x, max_y, AI);


    print_board(board, max_x, max_y);

	for (int i = 0; i < max_y; i++) {
		free(board[i]);
	}
    free(board);
	return 0;
}

__attribute__((destructor))
void destructor() {
    system("leaks a.out -q");
}