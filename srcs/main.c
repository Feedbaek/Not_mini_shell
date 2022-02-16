#include "../include/minishell.h"

static void print_banner()
{
    printf("  _   _       _     __  __ _       ");
    printf("_   ____  _          _ _ \n");
    printf(" | \\ | | ___ | |_  |  \\/  (_)_ ");
    printf("__ (_) / ___|| |__   ___| | |\n");
    printf(" |  \\| |/ _ \\| __| | |\\/| | | ");
    printf("'_ \\| | \\___ \\| '_ \\ / _ \\ | |\n");
    printf(" | |\\  | (_) | |_  | |  | | ");
    printf("| | | | |  ___) | | | |  __/ | |\n");
    printf(" |_| \\_|\\___/ \\__| |_|  |_|_|_|");
    printf(" |_|_| |____/|_| |_|\\___|_|_|\n");
}


int main(int ac, char **av)
{
    print_banner();
    if (ac == 1)
        printf(av[0]);
    return (0);
}
