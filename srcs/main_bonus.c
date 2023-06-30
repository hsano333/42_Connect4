#include <stdio.h>
#include "libft.h"
#include "connect4.h"

int main(int argc, char **argv)
{
    if (argc != 4){
        ft_putendl_fd("Error: Enter the gird size", 1);
        ft_putendl_fd("Ex: ./connect4 8 10 1", 1);
    }

    int x = ft_atoi(argv[1]);
    int y = atoi(argv[2]);
    int graphical = atoi(argv[2]);
    if ((7 <= x && x <= 100) || (6 <= y && 7 <= 100)){
        if(graphical){
            //connect4_graphical(x,y);
            ft_putendl_fd("Bonus Game", 1);
        }else{
            ft_putendl_fd("Mandatory Game", 1);
        }
    }else{
        ft_putendl_fd("Error: Invalid gird size", 1);
    }
                     
                     
                     
                     
    return (0);
}
