/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:32:20 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/30 15:47:09 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_state	g_state;

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

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	cpy_env(env);
	g_state.exit_status = 0;
	signal(SIGINT, (void *)handle_signal);
	signal(SIGQUIT, SIG_IGN);
	echoctl_off();
	print_banner();
	print_prompt();
	free_double_pointer(&g_state.envp);
	free_double_pointer(&g_state.path);
	g_state.exit_status = 130;
	return (g_state.exit_status);
}
