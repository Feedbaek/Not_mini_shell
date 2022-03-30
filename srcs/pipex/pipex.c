/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:53:38 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/30 21:58:04 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	connect_stdin(t_cmd *cmd_arg, int pipe_read, int pipe_write)
{
	int	fd;

	if (cmd_arg->limiter)
	{
		fd = open(cmd_arg->tmp, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (cmd_arg->redirect_in)
	{
		redirect_in(cmd_arg->redirect_in, STDIN_FILENO);
	}
	else
	{
		dup2(pipe_read, STDIN_FILENO);
	}
}

static void	connect_stdout(t_cmd *cmd_arg, int pipe_read, int pipe_write)
{
	if (cmd_arg->redirect_out_add)
	{
		redirect_out_add(cmd_arg->redirect_out_add, STDOUT_FILENO);
		if (pipe_write != STDOUT_FILENO)
			close(pipe_write);
	}
	else if (cmd_arg->redirect_out)
	{
		redirect_out(cmd_arg->redirect_out, STDOUT_FILENO);
		if (pipe_write != STDOUT_FILENO)
			close(pipe_write);
	}
	else
	{
		dup2(pipe_write, STDOUT_FILENO);
	}
}

static void	child_process(t_cmd *cmd_arg, int *pipe_a, int *pipe_b)
{
	int	read_fd;
	int	write_fd;

	if (cmd_arg->idx % 2 == 0)
	{
		read_fd = pipe_b[0];
		write_fd = pipe_a[1];
	}
	else
	{
		read_fd = pipe_a[0];
		write_fd = pipe_b[1];
	}
	if (cmd_arg->idx == 0)
		read_fd = STDIN_FILENO;
	if (cmd_arg->next == 0)
		write_fd = STDOUT_FILENO;
	connect_stdin(cmd_arg, read_fd, write_fd);
	connect_stdout(cmd_arg, read_fd, write_fd);
	run_execve(cmd_arg);
}

void	disconnect_redirect(t_cmd *cmd_arg, int *pipe_a, int *pipe_b)
{
	if (cmd_arg->idx % 2 == 0)
	{
		pipe(pipe_a);
		if (cmd_arg->idx != 0)
			close(pipe_b[1]);
		if (cmd_arg->next == 0)
		{
			close(pipe_a[0]);
			close(pipe_a[1]);
		}
	}
	else
	{
		pipe(pipe_b);
		close(pipe_a[1]);
		if (cmd_arg->next == 0)
		{
			close(pipe_b[0]);
			close(pipe_b[1]);
		}
	}
}

void	test_pipex(t_cmd *head)
{
	t_cmd	*parser;
	int		pipe_a[2];
	int		pipe_b[2];
	int		i;
	pid_t	here;

	here = fork();
	if (!here)
		here_doc(head);
	else
	{
		waitpid(here, &(g_state.exit_status), 0);
		printf("%d\n", g_state.exit_status);
		if (g_state.exit_status != 0)
		{
			write(1, "1\n", 2);
			wait_pid(head);
			return ;
		}
	}
	write(1, "44\n", 3);
	parser = head;
	while (parser && parser->cmd)
	{
		disconnect_redirect(parser, pipe_a, pipe_b);
		parser->pid = fork();
		if (!parser->pid)
			child_process(parser, pipe_a, pipe_b);
		parser = parser->next;
	}
	wait_pid(head);
}
