#include <stdio.h>
#include "libft.h"
#include "connect4.h"
#include <stddef.h>

//int main(int argc, char **argv)
//{
//    (void)argv;
//    if (argc != 3){
//        ft_putendl_fd("Error: Enter the gird size", 1);
//        ft_putendl_fd("Ex: ./connect4 8 10", 1);
//    }
//    return (0);
//}

void	make_array_and_game(int max_x, int max_y);
void	end_massage(int game_status);

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		end_massage(10);
		return (0);
	}
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	if ((7 <= x && x <= 100) && (6 <= y && y <= 100))
		make_array_and_game(x,y);
	else
		ft_putendl_fd("Error: Invalid grid size", 1);
	return (0);
}
