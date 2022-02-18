/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:32:20 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/18 10:38:51 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_banner(void)
{
	printf("\n  _   _       _     __  __ _       ");
	printf("_   ____  _          _ _ \n");
	printf(" | \\ | | ___ | |_  |  \\/  (_)_ ");
	printf("__ (_) / ___|| |__   ___| | |\n");
	printf(" |  \\| |/ _ \\| __| | |\\/| | | ");
	printf("'_ \\| | \\___ \\| '_ \\ / _ \\ | |\n");
	printf(" | |\\  | (_) | |_  | |  | | ");
	printf("| | | | |  ___) | | | |  __/ | |\n");
	printf(" |_| \\_|\\___/ \\__| |_|  |_|_|_|");
	printf(" |_|_| |____/|_| |_|\\___|_|_|\n\n\n");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	(void)envp;
	print_banner();
	printf("bash $");
	return (0);
}
