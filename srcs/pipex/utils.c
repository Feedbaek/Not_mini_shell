/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:47:05 by minskim2          #+#    #+#             */
/*   Updated: 2022/04/03 16:09:53 by minskim2         ###   ########.fr       */
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
	if (equals(cmd_arg->cmd, "echo"))
		ft_echo(cmd_arg->argv);
	else if (equals(cmd_arg->cmd, "cd"))
		ft_cd(cmd_arg->argv);
	else if (equals(cmd_arg->cmd, "pwd"))
		ft_pwd();
	else if (equals(cmd_arg->cmd, "export"))
		ft_export(cmd_arg->argv);
	else if (equals(cmd_arg->cmd, "unset"))
		ft_unset(cmd_arg->argv);
	else if (equals(cmd_arg->cmd, "env"))
		ft_env();
	else if (equals(cmd_arg->cmd, "exit"))
		ft_exit(cmd_arg->argv);
	else
	{
		echoctl_on();
		if (execve(cmd_arg->cmd, cmd_arg->argv, g_state.envp) == -1)
		{
			printf("bash: %s: %s\n", cmd_arg->cmd, "command not found");
			exit(127);
		}
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
