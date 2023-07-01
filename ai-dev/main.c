#include <stdio.h>
#include <stdlib.h>
#include "ai.h"
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
	board[0][max_y / 2] = YELLOW;
	ai(board, max_y / 2, max_x, max_y);
	return 0;
}