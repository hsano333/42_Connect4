/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:46:43 by tokazaki          #+#    #+#             */
/*   Updated: 2023/07/02 15:09:26 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ai.h"
#include <stdlib.h>
#include <time.h>

char	*get_next_line(int fd);

void	output_board(char **board, int max_x, int max_y);
int		check_enter_input(char **board, char *line, int max_x, int max_y);
int		input_board(char **board, int max_x, int max_y);
int		ai(char **board, int user_x , int max_x, int max_y);
int		draw_checkier(char **board, int max_x, int max_y);
void	free_board(char **board);

int	input_output(char **board, int max_x, int max_y)
{
	int	user_x;
	int	ai_x;
	int	game_status;

	srand(time(NULL));
	if (rand() % 100 < 50)
		board[0][max_x / 2] = 1;
	while(1)
	{
		output_board(board, max_x, max_y);//出力
		user_x = input_board(board, max_x, max_y);//入力受付
		game_status = 0;//勝つ/負ける判定関数
		game_status = draw_checkier(board, max_x, max_y);//引き分けの検知する関数
		if(game_status != 0)
		{
			if (ai_x == -1)
				game_status = -1;
			break;
		}
		ai_x = ai(board, user_x , max_x, max_y);//aiの処理
		set_board(&board, ai_x, max_y, AI);
		game_status = 0;//勝つ/負ける判定関数
		game_status = draw_checkier(board, max_x, max_y);//引き分けの検知する関数
		if(game_status != 0 || ai_x == -1)
		{
			if (ai_x == -1)
				game_status = -1;
			break;
		}
	}
	return (game_status);
}

void	output_board(char **board, int max_x, int max_y)
{
	int	i;

	i = 1;
	while (board[max_y - i])
	{
		for (int k = 0; k < max_x; k++)
			write(1,"+-",2);
		write(1,"+\n",2);
		write(1,"|",1);
		for(int j = 0; j < max_x; j++)
		{
			char tmp = board[max_y - i][j];
			if (tmp == 0)
			{
				write (1,"\x1b[0m",4);
				write(1," ",1);
			}
			else if (tmp == 1)
			{
				write (1, "\x1b[31m",5);
				write(1,"0",1);
			}
			else if (tmp == 2)
			{
				write (1, "\x1b[33m",5);
				write(1,"0",1);
			}
			
			write (1,"\x1b[0m",4);
			write(1,"|",1);
		}
		write(1,"\n",1);
		
		i++;
	}
		for (int k = 0; k < max_x; k++)
			write(1,"+-",2);
		write(1,"+\n",2);
}

int	input_board(char **board, int max_x, int max_y)
{
	char	*line;
	int		user_x;

	ft_putendl_fd("please fill in the value", 1);//入力してください
	while(1)
	{
		line = get_next_line(0);//標準入力を受け付ける
		user_x = check_enter_input(board, line, max_x, max_y);//返り値を検査する
		free (line);
		if (user_x != -1)
			break ;
		ft_putendl_fd("please fill in the correct value", 1);//入力してください
	}
	return (user_x);
}

int	check_enter_input(char **board, char *line, int max_x, int max_y)//返り値を検査する
{
	int	user_x;
	int	i;

	i = 0;
	user_x = 0;
	while (ft_isdigit(line[i]) && i < 4)//厳密atoi
	{
		user_x  = user_x * 10 + (line[i] - '0');
		i++;
	}
	if (!(0 < user_x && user_x <= max_x) || !(line[i] == '\n' && line[i + 1] == '\0'))
		return (-1);
	i = 0;
	while(i < max_y)//置きたい所にスペースがあるか確認
	{
		if (board[i][user_x - 1] == 0)
		{
			board[i][user_x - 1] = 1;
			return (user_x);
		}
		i++;
	}
	return (-1);
}

// int		ai(char **board, int user_x , int max_x, int max_y)//簡易ai
// {
// 	int	i;
// 	int	j;

// 	(void)user_x;
// 	i = 0;
// 	while(i < max_x)
// 	{
// 		j = 0;
// 		while(j < max_y)
// 		{
// 			if (board[j][i] == 0)
// 			{
// 				board[j][i] = 1;
// 				return (i);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	draw_checkier(char **board, int max_x, int max_y)//drawnチェッカー
{
	for( int i = 0;i < max_x; i++)
	{
		if (board[max_y - 1][i] == 0)
		{
			return(0);
		}
	}
	return (3);
}
