/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:53:38 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/01 20:12:10 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	connect_pipe(int pipefd[2], int fd)
{
	dup2(pipefd[fd], fd);
	close(pipefd[0]);
	close(pipefd[1]);
}

static void	cmd_init(const char *line, t_cmd *x, char **envp)
{
	char	**split;

	split = minskim2_split(line, ' ');
	if (!split)
	{
		printf("split error: %s\n", strerror(errno));
		exit(1);
	}
	if (!path_finder(envp, x, split[0]))
	{
		printf("init error: %s\n", strerror(errno));
		exit(1);
	}
	x->argv = split;
	x->envp = envp;
	x->next = 0;
}

static void	parent_proc(char **argv, char **envp, t_cmd *cmd_arg)
{
	redirect_out(argv[4]);
	connect_pipe(cmd_arg->pipe, STDIN_FILENO);
	cmd_init(argv[3], cmd_arg, envp);
	waitpid(cmd_arg->pid, &(cmd_arg->status), WNOWAIT);
	if (execve(cmd_arg->cmd, cmd_arg->argv, envp) == -1)
	{
		printf("parent error: %s\n", strerror(errno));
		exit(1);
	}
}

static void	child_proc(char **argv, char **envp, t_cmd *cmd_arg)
{
	redirect_in(argv[1]);
	connect_pipe(cmd_arg->pipe, STDOUT_FILENO);
	cmd_init(argv[2], cmd_arg, envp);
	if (execve(cmd_arg->cmd, cmd_arg->argv, envp) == -1)
	{
		printf("child error: %s\n", strerror(errno));
		exit(1);
	}
}

int	check_length(char **split)
{
	int	cnt;

	cnt = 0;
	if (!split)
		exit(1);
	while(*split)
	{
		cnt++;
		split++;
	}
	return (cnt);
}

static void	set_pipex(char **argv, t_cmd **head, char **envp)
{
	char	**split;
	int		cnt;
	int		i;
	t_cmd	*cmd_arg;
	t_cmd	*prev_cmd;

	split = ft_split(argv, '|');
	cnt = check_length(split);
	i = 0;
	while (i < cnt)
	{
		cmd_arg = malloc(sizeof(t_cmd));
		if (!cmd_arg)
			exit(1);
		if (i == 0)
		{
			*head = cmd_arg;
			prev_cmd = cmd_arg;
		}
		pipe(cmd_arg->pipe);
		prev_cmd->next = cmd_arg;
		prev_cmd = cmd_arg;
		cmd_init(split[i], cmd_arg, envp);
	}
}

void	run_execve(t_cmd *cmd_arg, int prev_fd)
{

	//connect_pipe(prev_fd, STDIN_FILENO);
	dup2(prev_fd, STDIN_FILENO);
	//connect_pipe(next_fd, STDOUT_FILENO);
	dup2(cmd_arg->pipe[1], STDOUT_FILENO);
	if (execve(cmd_arg->cmd, cmd_arg->argv, cmd_arg->envp) == -1)
	{
		printf("run_execve error: %s\n", strerror(errno));
		exit(1);
	}
}

void	test_pipex(t_cmd **head, int input_fd, int output_fd)
{
	t_cmd	*parser;
	t_cmd	*prev;

	parser = *head;
	while (parser)
	{
		parser->pid = fork();
		waitpid(parser->pid, &(parser->status), WNOWAIT);
		if (!parser->pid)
		{
			if (!parser->next)
				dup2(parser->pipe[0], output_fd);
			if (parser == *head)
				run_execve(parser, input_fd);
			else
				run_execve(parser, prev->pipe[0]);
		}
		prev = parser;
		parser = parser->next;
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_cmd	*head;
	int	input_fd;
	int	output_fd;

	input_fd = 0;
	output_fd = 1;
	set_pipex(argv, &head, envp);
	test_pipex(&head, input_fd, output_fd);
	return (0);
}
