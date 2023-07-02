#include <stdio.h>
#include "ai2.h"

void set_board(char ***board, int put_x, int width, int height, char turn) {
    for (int i = 0; i < height; i++) {
        if ((*board)[i][put_x] == BLANK) {
            (*board)[i][put_x] = turn;
            break;
        }
    }
    
}

void print_board(char **board, int width, int height) {
	int i, j;
	for (i = height - 1; 0 <= i; i--)
	// for (i = 0; i < height; i++)	
	{
		// printf("%2d ", height - i);
		printf("%2d ", i);
		for (j = 0; j < width; j++)
		{
			printf("%c ", (board[i][j] == '\0' ? ' ' : (board[i][j] == AI ? 'o' : 'x')));
		}
		printf("\n");
	}
	printf("   ");
	for (i = 0; i < width; i++) {
		printf("%d ", i);
	}
	printf("\n");
	printf("--------------------------------------------\n");
}
