/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:47:05 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/30 16:31:28 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	minskim2_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	if (i == n)
		i--;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void	run_execve(t_cmd *cmd_arg)
{
	if (execve(cmd_arg->cmd, cmd_arg->argv, g_state.envp) == -1)
	{
		printf("bash: %s: %s\n", cmd_arg->cmd, "command not found");
		exit(127);
	}
}

void	wait_pid(t_cmd *cmd_arg)
{
	t_cmd	*parser;

	parser = cmd_arg;
	while (parser)
	{
		waitpid(parser->pid, &(parser->status), 0);
		g_state.exit_status = parser->status / 256;
		parser = parser->next;
	}
	parser = cmd_arg;
	while (parser)
	{
		if (parser->limiter)
			unlink(parser->tmp);
		parser = parser->next;
	}
}

void	print_str_error(char *str)
{
	printf("bash: %s: %s\n", str, strerror(errno));
	exit(1);
}
