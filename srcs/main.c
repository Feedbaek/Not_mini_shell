#include "../include/minishell.h"
#include <stdio.h>

static void print_banner()
{
    printf("  _   _       _     __  __ _       _   ____  _          _ _ \n");
    printf(" | \\ | | ___ | |_  |  \\/  (_)_ __ (_) / ___|| |__   ___| | |\n");
    printf(" |  \\| |/ _ \\| __| | |\\/| | | '_ \\| | \\___ \\| '_ \\ / _ \\ | |\n");
    printf(" | |\\  | (_) | |_  | |  | | | | | | |  ___) | | | |  __/ | |\n");
    printf(" |_| \\_|\\___/ \\__| |_|  |_|_|_| |_|_| |____/|_| |_|\\___|_|_|\n");
}


int main(int ac, char **av)
{
    print_banner();
    if (ac == 1)
        printf(av[0]);
    return (0);
}
