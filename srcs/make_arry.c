/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:40:48 by tokazaki          #+#    #+#             */
/*   Updated: 2023/07/02 14:18:11 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "connect4.h"

void	make_array_and_game(int max_x, int max_y);
char	**make_array(int max_x, int max_y);
void	free_board(char **board);
void	end_massage(int game_status);
int		input_output(char **board, int max_x, int max_y);

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q connect4");
// }

// int	main(int argc, char **argv)
// {
// 	if (argc != 3)
// 	{
// 		end_massage(10);
// 		return (0);
// 	}
// 	int x = atoi(argv[1]);
// 	int y = atoi(argv[2]);
// 	if ((7 <= x && x <= 100) && (6 <= y && y <= 100))
// 		make_array_and_game(x,y);
// 	else
// 		ft_putendl_fd("Error: Invalid grid size", 1);
// 	return (0);
// }

void	make_array_and_game(int max_x, int max_y)
{
	char	**board;
	int		game_status;

	board = make_array(max_x, max_y);
	if (!board)
	{
		ft_putendl_fd("ERROR : out-of-memory", 1);
		return ;
	}
	game_status = input_output(board, max_x, max_y);
	free_board(board);
	end_massage(game_status);
}

char	**make_array(int max_x, int max_y)
{
	char	**board;
	int		i;

	i = 0;
	board = (char **)malloc(sizeof(char*) * (max_y + 1));
	if (!board)
		return (NULL);
	while(i < max_y)
	{
		board[i] = (char *)calloc(max_x, sizeof(char));
		if(!board[i])
		{
			free_board (board);
			return (NULL);
		}
		i++;
	}
	board[max_y] = NULL;
	return (board);
}

void	free_board(char **board)
{
	int	i;

	i = 0;
	while(board[i] != NULL)
	{
		free(board[i]);
		i++;
	}
	free(board);
}

void	end_massage(int game_status)
{
	if (game_status == 1)//player win
		ft_putendl_fd("Congratulations, you win!", 1);
	else if (game_status == 2)//player lose
		ft_putendl_fd("you lose...", 1);
	else if (game_status == 3)//draw
		ft_putendl_fd("It's a draw!", 1);
	else if (game_status == -1)//error
		ft_putendl_fd("ERROR:", 1);
	else if (game_status == 10)//初期error
	{
        ft_putendl_fd("Error: Enter the gird size", 1);
        ft_putendl_fd("Ex: ./connect4 8 10", 1);
	}
}
