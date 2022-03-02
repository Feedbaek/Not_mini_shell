/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:53:38 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/02 18:15:57 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int		cnt;
	int		i;
	t_cmd	*cmd_arg;
	t_cmd	*prev_cmd;

	cnt = check_length(argv);
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
		//pipe(cmd_arg->pipe);
		prev_cmd->next = cmd_arg;
		prev_cmd = cmd_arg;
		cmd_init(argv[i], cmd_arg, envp);
		cmd_arg->idx = i;
		i++;
	}
}

void	run_execve(t_cmd *cmd_arg, int prev_fd)
{
	//connect_pipe(prev_fd, STDIN_FILENO);
	//printf("error4: %s\n", cmd_arg->cmd);
	dup2(prev_fd, STDIN_FILENO);
	if (prev_fd != 0)
		close(prev_fd);
	//printf("error5: %s, %s\n", cmd_arg->cmd, cmd_arg->argv[0]);
	//connect_pipe(next_fd, STDOUT_FILENO);
	dup2(cmd_arg->pipe[1], STDOUT_FILENO);
	close(cmd_arg->pipe[1]);
	//printf("error6: %s\n", cmd_arg->cmd);
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
	int		pipe_a[2];
	int		pipe_b[2];

	parser = *head;
	while (parser)
	{
		parser->pid = fork();
		if (!parser->pid)
		{
			if (!parser->next)
			{
				dup2(parser->pipe[0], output_fd);
				close(parser->pipe[0]);
			}
			if (parser == *head)
				run_execve(parser, input_fd);
			else
				run_execve(parser, prev->pipe[0]);
		}
		else
			waitpid(parser->pid, &(parser->status), WNOWAIT);
		prev = parser;
		parser = parser->next;
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_cmd	*head;
	int	input_fd;
	int	output_fd;

	(void)argc;
	input_fd = 0;
	output_fd = 1;
	//printf("%s\n", *(argv+1));
	set_pipex(argv+1, &head, envp);
	//printf("%s\n", head->cmd);
	test_pipex(&head, input_fd, output_fd);
	return (0);
}
