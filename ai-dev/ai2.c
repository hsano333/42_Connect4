#include <stdlib.h>
#include "ai2.h"

int ai(char **board, int player_put_x, int width, int height) {
	static int *col_index;
	int score;
	int max_score;
	char turn;

	if (col_index == NULL) {
		col_index = calloc(width, sizeof(int));
		if (col_index == NULL) {
			return -1;
		}
		for (int i = 0; i < width; i++) {
			col_index[i] = -1;
		}	
	}
	col_index[player_put_x]++;

	for (int i = 0; i < width; i++) {
		if (0 <= col_index[i] && col_index[i] < height) {
			if (board[col_index[i]][i] == RED && col_index[i] < height - 1) {
				return i;
			}
		}
	}
	for (int i = 0; i < width / 2; i++) {
		if (col_index[width / 2 + i < height])
		{
			return width / 2 + i;
		}
		if (col_index[width / 2 - i < height])
		{
			return width / 2 - i;
		}
	}
	return 0;
}