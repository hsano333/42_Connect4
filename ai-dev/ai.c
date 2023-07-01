#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include "ai.h"


#include <stdio.h>
#include "utils.h"

bool is_inboard(int x, int y, int max_x, int max_y) {
	return (0 <= (x) && (x) < (max_x) && 0 <= (y) && (y) < (max_y));
}
const int adjacent[8][2] = {
	{-1, 0},
	{-1, 1},
	{0, 1},
	{1, 1},
	{1, 0},
	{1, -1},
	{0, -1},
	{-1, -1}
};

int max(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

int min(int a, int b) {
	if (a > b) {
		return b;
	} else {
		return a;
	}
}

int get_top(char *col) {
	int i;
	
	i = 0;
	while (col[i] != '\0' && col[i] != UNPLACED) {
		i++;
	}
	return (i - 1);
}

int get_connect_len(char **board, int x, int y, int max_x, int max_y, const int *direction) {
	int sum;
	sum = 0;
	for (int i = 0; is_inboard(x + (i * direction[0]), y + (i * direction[1]), max_x, max_y); i++) {
		if (board[y + (i * direction[1])][x + (i * direction[0])] != board[y][x]) {
			break;
		}
		sum++;
	}
	for (int i = -1; is_inboard(x + (i * direction[0]), y + (i * direction[1]), max_x, max_y); i--) {
		if (board[y + (i * direction[1])][x + (i * direction[0])] != board[y][x]) {
			break;
		}
		sum++;
	}
	return sum;
}

bool is_win(char **board, int put_x, int max_x, int max_y) {
	int put_y;
	int sum;

	put_y = get_top(board[put_x]);
	sum = 0;
	for (int i = 0; i < 4; i++) {
		if (4 <= get_connect_len(board, put_x, put_y, max_x, max_y, adjacent[i])) {
			return true;
		}
	}
	return false;
}

int eval(char **board, int x, int y, int max_x, int max_y) {
	int score = 0;
	int connect_len;
	for (int i = 0; i < 4; i++)
	{
		connect_len = get_connect_len(board, x, y, max_x, max_y, adjacent[i]);
		if (4 <= connect_len) {
			return INT_MAX;
		} else if (connect_len == 3) {
			score += 10000;
		} else if (connect_len == 2) {
			score += 100;
		} else if (connect_len == 1) {
			score += 1;
		}
	}

	printf("turn : %c [x, y] : [%2d, %2d], score : %d\n", board[y][x], x, y, score);
	print_board(board, max_x, max_y);

	return score;
}

int minimax(char **board, int player_put_x, int max_x, int max_y, int max_depth, int *col_index) {
	char turn;
	int best_score;
	int score;

	if (max_depth == 0) {
		return (INT_MIN);
	}
	turn = board[col_index[player_put_x]][player_put_x] ^ (RED ^ YELLOW);
	best_score = eval(board, player_put_x, col_index[player_put_x], max_x, max_y);

	// printf("player_put_x: %2d ,max_depth: %d, max_score: %d\n", player_put_x, max_depth, max_score); //
	// print_board(board, max_x, max_y); //

	if (turn == YELLOW) {
		best_score *= -1;
	}
	for (int i = 0; i < max_x && best_score != INT_MAX; i++) {
		if (col_index[i] + 1 != max_y) {
			col_index[i]++;
			board[col_index[i]][i] = turn;
			score = eval(board, i, col_index[i], max_x, max_y);
			if (turn == YELLOW) {
				score *= -1;
				if (score <= best_score) {
					best_score = score;
					best_score = min(best_score, minimax(board, i, max_x, max_y, max_depth - 1, col_index));
				}
			} else {
				if (best_score <= score) {
					best_score = score;
					best_score = max(best_score, minimax(board, i, max_x, max_y, max_depth - 1, col_index));
				}
			}
			board[col_index[i]][i] = UNPLACED;
			col_index[i]--;
		}
	}
	if (turn == YELLOW) {
		best_score *= -1;
	}
	return best_score;
}

int ai(char **board, int player_put_x, int width, int height) {
	static int *col_index;
	int score;
	int max_score;
	int best_index;
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
	max_score = INT_MIN;
	best_index = -1;
	col_index[player_put_x]++;
	turn = board[col_index[player_put_x]][player_put_x] ^ (RED ^ YELLOW);
	// print_board(board, width, height);
	for (int i = 0; i < width; i++)
	{
		fprintf(stderr, "i : '%d'\n", i);
		col_index[i]++;
		board[col_index[i]][i] = turn;
		score = minimax(board, i, width, height, 10, col_index);
		if (max_score < score) {
			fprintf(stderr, "update ");
			best_index = i;
			max_score = score;
		}
			fprintf(stderr, "max_score : '%d' ", max_score);
			fprintf(stderr, "index : '%d'\n", i);
		board[col_index[i]][i] = UNPLACED;
		col_index[i]--;
	}
	fprintf(stderr, "max_score : '%d'\n", max_score);
	fprintf(stderr, "best_index : '%d'\n", best_index);
	return best_index;
}