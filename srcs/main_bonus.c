#include <stdio.h>
#include "libft.h"
#include "connect4.h"
#include "connect4_graphical.h"
#include "board.h"


//#include <stdio.h>
//__attribute__((destructor)) void f(void){
    //system("leaks connect4");
//}
void	make_array_and_game(int max_x, int max_y);

int main(int argc, char **argv)
{
    if (argc != 4){
        ft_putendl_fd("Error: Enter the gird size and whether graphical is or not", 1);
        ft_putendl_fd("Ex: ./connect4 8 10 1", 1);
        return (1);
    }

    int x = ft_atoi(argv[1]);
    int y = ft_atoi(argv[2]);
    int graphical = ft_atoi(argv[3]);
    if ((7 <= x && x <= GRID_MAX) && (6 <= y && y <= GRID_MAX)){
        if(graphical == 1){
            connect4_graphical(x,y);
        }else{
            make_array_and_game(x,y);
        }
    }else{
        ft_putendl_fd("Error: Invalid gird size", 1);
        return (1);
    }
                     
    return (0);
}
