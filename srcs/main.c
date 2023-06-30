#include <stdio.h>
#include "libft.h"
#include "connect4.h"

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 3){
        ft_putendl_fd("Error: Enter the gird size", 1);
        ft_putendl_fd("Ex: ./connect4 8 10", 1);
    }
    return (0);
}
