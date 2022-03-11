/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:35:26 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/11 15:29:14 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);

	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		ft_putendl_fd("start bash on signal func\n", 1);
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		// rl_redisplay();
	}
}

void	handle_signal2(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGQUIT)
	{
		if (pid != -1)
		{
			write(1, "Quit: 3\n", 8);
			g_state.exit_status = 131;
		}
	}
}
