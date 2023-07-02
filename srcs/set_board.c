#include "ai.h"

void set_board(char ***board, int put_x, int height, char turn) {
	for (int i = 0; i < height; i++) {
		if ((*board)[i][put_x] == BLANK) {
			(*board)[i][put_x] = turn;
			break;
		}
	}
	
}
