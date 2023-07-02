#include <stdlib.h>
#include <stdbool.h>
#include "ai.h"

#include <stdio.h>

int min(int a, int b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

int max(int a, int b) {
	if (a < b) {
		return b;
	} else {
		return a;
	}
}

// static void set_o(char ***board, int width, int height) {
// 	for (int i = 0; i < height; i++) {
// 		for (int j = 0; j < width; j++)
// 		{
// 			(*board)[i][j] = 'o';
// 		}
// 	}
// }

// static void print_board(char *board[], int height) {
// 	for (int i = 0; i < height; i++) {
// 		printf("%s\n", board[i]);
// 	}
// 	printf("\n");
	
// }

bool is_inboard(int x, int y, int max_x, int max_y) {
	return (0 <= (x) && (x) < (max_x) && 0 <= (y) && (y) < (max_y));
}

int max_connect(char **board, int point_x, int point_y, int width, int height) {
	int max_connect_len;
	int connect_len;
	char turn;

	max_connect_len = 0;

	turn = board[point_y][point_x];

	// yoko
	connect_len = 0;
	for (int i = max(0, point_x - 3); i < width; i++) {
		if (board[point_y][i] == turn) {
			connect_len++;
		} else {
			max_connect_len = max(max_connect_len, connect_len);
			connect_len = 0;
		}
	}
	max_connect_len = max(max_connect_len, connect_len);
	// tate
	connect_len = 0;
	for (int i = max(0, point_y - 3); i < height; i++) {
		if (board[i][point_x] == turn) {
			connect_len++;
		} else {
			max_connect_len = max(max_connect_len, connect_len);
			connect_len = 0;
		}
	}
	max_connect_len = max(max_connect_len, connect_len);

	// oox
	// oxo
	// xoo

	connect_len = 0;
	for (int i = -3; i <= 3; i++) {
		if (is_inboard(point_x + i, point_y + i, width, height)) {
			if (board[point_y + i][point_x + i] == turn) {
				connect_len++;
			} else {
				max_connect_len = max(max_connect_len, connect_len);
				connect_len = 0;
			}
		}
	}
	max_connect_len = max(max_connect_len, connect_len);
	// xoo
	// oxo
	// oox

	connect_len = 0;
	for (int i = -3; i <= 3; i++) {
		if (is_inboard(point_x + i, point_y - i, width, height)) {
			if (board[point_y - i][point_x + i] == turn) {
			connect_len++;
			} else {
				max_connect_len = max(max_connect_len, connect_len);
				connect_len = 0;
			}
		}
	}
	max_connect_len = max(max_connect_len, connect_len);
	return max_connect_len;
}

bool is_win(char **board, int point_x, int point_y, int width, int height) {
	int connect = max_connect(board, point_x, point_y, width, height);
	if (4 <= connect) {
		return true;
	} else {
		return false;
	}
}

int will_player_win(char **board, int *col_index, int width, int height) {
	bool is_player_win;

	is_player_win = false;
	for (int i = 0; i < width; i++)
	{
		col_index[i]++;
		board[col_index[i]][i] = PLAYER;
		is_player_win = is_win(board, i, col_index[i], width, height);
		board[col_index[i]][i] = BLANK;
		col_index[i]--;
		if (is_player_win) {
			return i;
		}
	}
	return -1;
}

int *get_col_index(char **board, int width, int height) {
	int *col_index;

	col_index = calloc(width + 1, sizeof(int));
	if (col_index == NULL) {
		return NULL;
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (board[j][i] == BLANK) {
				col_index[i] = j - 1;
				break;
			}
		}
	}
	return col_index;
}

int ai(char **board, int player_put_x, int width, int height) {
	int *col_index;
	int result;

	col_index = get_col_index(board, width, height);
	if (col_index == NULL) {
		return -1;
	}
	for (int i = 0; i < width; i++)
	{
		printf("%d ", col_index[i]);
	}
	printf("\n");
	

	result = will_player_win(board, col_index, width, height);
	if (result != -1) {
		free(col_index);
		return result;
	}

	for (int i = 0; i < width; i++) {
		if (0 <= col_index[i] && col_index[i] < height) {
			if (board[col_index[i]][i] == AI && col_index[i] < height - 1) {
				free(col_index);
				return i;
			}
		}
	}
	for (int i = 0; i < width / 2; i++) {
		if (col_index[width / 2 + i < height]) {
			free(col_index);
			return width / 2 + i;
		}
		if (col_index[width / 2 - i < height]) {
			free(col_index);
			return width / 2 - i;
		}
	}
	(void)(player_put_x);
	free(col_index);
	return -1;
}