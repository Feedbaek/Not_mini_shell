/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:35:26 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/15 09:47:31 by sungmcho         ###   ########.fr       */
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
		if (pid == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			if (rl_on_new_line() == -1)
				exit(1);
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
}
