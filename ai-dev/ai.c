#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include "ai.h"


#include <stdio.h>
#include "utils.h"

bool is_inboard(int x, int y, int max_x, int max_y) {
	fprintf(stdout, "max_x : '%d'\n", max_x);
	fprintf(stdout, "max_y : '%d'\n", max_y);
	fprintf(stdout, "x : '%d'\n", x);
	fprintf(stdout, "y : '%d'\n", y);
	fprintf(stdout, "0 <= (x) && (x) < (max_x) && 0 <= (y) && (y) < (max_y) : '%d'\n", 0 <= (x) && (x) < (max_x) && 0 <= (y) && (y) < (max_y));
	return (0 <= (x) && (x) < (max_x) && 0 <= (y) && (y) < (max_y));
}

bool is_inboard_direction(int x, int y, int max_x, int max_y, const int direction[2]) {
	fprintf(stdout, "x : '%d'\n", x);
	fprintf(stdout, "y : '%d'\n", y);
	fprintf(stdout, "x + direction[0] : '%d'\n", x + direction[0]);
	fprintf(stdout, "y + direction[1] : '%d'\n", y + direction[1]);;
	return is_inboard(x + direction[0], y + direction[1], max_x, max_y);
}

bool is_inboard_rev_direction(int x, int y, int max_x, int max_y, const int direction[2]) {
	fprintf(stdout, "x : '%d'\n", x);
	fprintf(stdout, "y : '%d'\n", y);
	fprintf(stdout, "x + direction[0] : '%d'\n", x - direction[0]);
	fprintf(stdout, "y + direction[1] : '%d'\n", y - direction[1]);
	return is_inboard(x - direction[0], y - direction[1], max_x, max_y);
}


int adjacent[8][2] = {
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
	return sum;
}

int get_invite_connect_len(char **board, int x, int y, int max_x, int max_y, const int *direction) {
	int sum;
	int rev_direction[2];

	rev_direction[0] = direction[0] * -1;
	rev_direction[1] = direction[1] * -1;

	sum = get_connect_len(board, x, y, max_x, max_y, direction);
	sum = get_connect_len(board, x, y, max_x, max_y, rev_direction);
	return sum;
}

bool is_win(char **board, int put_x, int max_x, int max_y) {
	int put_y;
	int sum;

	put_y = get_top(board[put_x]);
	sum = 0;
	for (int i = 0; i < 4; i++) {
		if (4 <= get_invite_connect_len(board, put_x, put_y, max_x, max_y, adjacent[i])) {
			return true;
		}
	}
	return false;
}

/*
int calc_score(char **board, int max_x, int max_y, char eval_char)
{
	int connect_len;
	int score;

	print_board(board, max_x, max_y);
	score = 0;
	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++) {
			if (board[i][j] == eval_char) {
				for (int k = 0; k < 4; k++) {
					connect_len = 0;
					if (is_inboard_direction(i, j, max_x, max_y, adjacent[k])) {
						int deb_i = i - (int)(adjacent[k][1]);
						int deb_j = j - (int)(adjacent[k][0]);
						fprintf(stderr, "i - adjacent[k][0] : '%d'\n", i - adjacent[k][0]);
						fprintf(stderr, "j - adjacent[k][1] : '%d'\n", j - adjacent[k][1]);
						if (!is_inboard_rev_direction(i, j, max_x, max_y, adjacent[k]) 
						|| (board[i - adjacent[k][0]][j - adjacent[k][1]] != 
						board[i][j])) {
							connect_len = get_connect_len(board, j, i, max_x, max_y, adjacent[k]);
						}
					}
					{
						if (4 <= connect_len) {
							return INT_MAX;
						} else if (connect_len == 3) {
							score += 10000;
						} else if (connect_len == 2) {
							score += 100;
						} else {
							score += 1;
						}
					}
				}
			}
		}
	}
	return score;
}
*/

int get_len_score(int len) {
	int score;

	score = 0;
	if (4 <= len) {
		return INT_MAX / 2;
	} else if (len == 3) {
		score += 10000;
	} else if (len == 2) {
		score += 100;
	} else if (len == 1) {
		score += 1;
	}
	return score;
}

int calc_score(char **board, int max_x, int max_y, char eval_char) {
	int score = 0;
	int len;
	// yoko
	for (int i = 0; i < max_y; i++) {
		len = 0;
		for (int j = 0; j < max_x; j++) {
			if (board[i][j] == eval_char) {
				len++;
			}
			if (board[i][j] != eval_char || j == max_x - 1) {
				score += get_len_score(len);
				len = 0;
				if (INT_MAX / 2 <= score + 10) {
					return score;
				}
			}
		}
	}
printf("score %c : '%d'\n", eval_char, score);
	// tate 
	for (int j = 0; j < max_x; j++) {
		len = 0;
		for (int i = 0; i < max_y; i++) {
			if (board[i][j] == eval_char) {
				len++;
			}
			if (board[i][j] != eval_char || i == max_y - 1) {
				score += get_len_score(len);
				len = 0;
				if (INT_MAX / 2 <= score + 10) {
					return score;
				}
			}
		}
	}
printf("score %c : '%d'\n", eval_char, score);
	// naname 
	// xoo
	// oxo
	// oox
	for (int i = 0; i < max_x; i++) {
		len = 0;
		for (int j = 0; 0 <= i - j && j < max_y; j++) {
			fprintf(stderr, "len : '%d', %d, %d\n", len, i, j);
			if (board[j][i - j] == eval_char) {
				len++;
				fprintf(stderr, "len : '%d', %d, %d\n", len, i, j);
			}
			if (board[j][i - j] != eval_char) {
				score += get_len_score(len);

				len = 0;
				if (INT_MAX / 2 <= score + 10) {
					return score;
				}
			}
		}
		score += get_len_score(len);
	}
	for (int j = 0; j < max_y; j++) {
		for (int i = 0; i < max_x && 0 <= max_x - 1 - j ; i++) {
			if (board[j][max_x - 1 - j] == eval_char) {
				len++;
			}
			if (board[j][max_x - 1 - j] != eval_char) {
				fprintf(stderr, "len : '%d'\n", len);
				score += get_len_score(len);
				len = 0;
				if (INT_MAX / 2 <= score + 10) {
					return score;
				}
			}
		}
		score += get_len_score(len);
	}
printf("score %c : '%d'\n", eval_char, score);
	// naname 
	// oox
	// oxo
	// xoo
	for (int i = 0; i < max_x; i++) {
		len = 0;
		for (int j = 0; i + j < max_x && j < max_y; j++) {
			if (board[j][i + j] == eval_char) {
				len++;
			}
			if (board[j][i + j] != eval_char) {
				score += get_len_score(len);
				len = 0;
				if (INT_MAX / 2 <= score + 10) {
					return score;
				}
			}
		}
		score += get_len_score(len);
	}
	for (int j = 0; j < max_y; j++) {
		for (int i = 0; i < max_x && j + i < max_y ; i++) {
			if (board[j][j + i] == eval_char) {
				len++;
			}
			if (board[j][j + i] != eval_char) {
				score += get_len_score(len);
				len = 0;
				if (INT_MAX / 2 <= score + 10) {
					return score;
				}
			}
		}
		score += get_len_score(len);
	}




	printf("score %c : '%d'\n", eval_char, score);
	print_board(board, max_x, max_y);
	return score;
}


int eval(char **board, int x, int y, int max_x, int max_y) {
	// int score = 0;



	// int connect_len;
	// for (int i = 0; i < 4; i++)
	// {
	// 	connect_len = get_invite_connect_len(board, x, y, max_x, max_y, adjacent[i]);
	// 	if (4 <= connect_len) {
	// 		return INT_MAX;
	// 	} else if (connect_len == 3) {
	// 		score += 10000;
	// 	} else if (connect_len == 2) {
	// 		score += 100;
	// 	} else if (connect_len == 1) {
	// 		score += 1;
	// 	}
	// }
	int yellow_score = 0;
	int red_score = 0;
	yellow_score += calc_score(board, max_x, max_y, YELLOW);
	red_score -= calc_score(board, max_x, max_y, RED);
	// printf("yellow_score : %d, red_score : '%d, '\n", yellow_score, red_score);
	// printf("turn : %c [x, y] : [%2d, %2d], score : %d\n", board[y][x], x, y, yellow_score + red_score);
	// print_board(board, max_x, max_y);

	return yellow_score + red_score;
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
			if (turn == RED) {
				score *= -1;
				if (score <= best_score) {
					best_score = score;
					best_score = min(best_score, minimax(board, i, max_x, max_y, max_depth - 1, col_index));
					fprintf(stderr, "update : '%d'\n", best_score);
				}
			} else {
				if (best_score <= score) {
					best_score = score;
					best_score = max(best_score, minimax(board, i, max_x, max_y, max_depth - 1, col_index));
					fprintf(stderr, "update : '%d'\n", best_score);
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
		score = minimax(board, i, width, height, 5, col_index);
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