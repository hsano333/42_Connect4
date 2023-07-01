#include <stdio.h>

void print_board(char **board, int width, int height) {
	int i, j;
	for (i = height - 1; 0 <= i; i--)
	// for (i = 0; i < height; i++)	
	{
		// printf("%2d ", height - i);
		printf("%2d ", i);
		for (j = 0; j < width; j++)
		{
			printf("%c ", (board[i][j] == '\0' ? ' ' : board[i][j]));
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
