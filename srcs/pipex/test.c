/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:53:38 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/11 18:32:25 by minskim2         ###   ########.fr       */
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
		prev_cmd->next = cmd_arg;
		prev_cmd = cmd_arg;
		cmd_init(argv[i], cmd_arg, envp);
		cmd_arg->idx = i;
		i++;
	}
}

void	run_execve(t_cmd *cmd_arg, int pipe_read, int pipe_write)
{
/*
	if ('<<'이 있다면)
		here_doc("limiter", STDIN_FILENO);
	else
	{
		if ('<'이 있다면)
			redirect_in(file, STDIN_FILENO);
		else
			dup2(pipe_read, STDIN_FILENO);
	}
	if ('>>'이 있다면)
		redirect_out_add(file, STDOUT_FILENO);
	else
	{
		if ('>' 이 있다면)
			redirect_out(file, STDOUT_FILENO);
		else
			dup2(pipe_write, STDOUT_FILENO);
	}
*/
	dup2(pipe_read, STDIN_FILENO);
	dup2(pipe_write, STDOUT_FILENO);
	if (execve(cmd_arg->cmd, cmd_arg->argv, cmd_arg->envp) == -1)
	{
		printf("run_execve error: %s\n", strerror(errno));
		exit(1);
	}
}

void	connect_redirect(t_cmd *cmd_arg, int *pipe_a, int *pipe_b)
{
	if (cmd_arg->idx % 2 == 0)	// 인덱스 짝수의 경우
	{
		pipe(pipe_a);
		if (cmd_arg->idx != 0)	// 처음 명령어가 아닌경우 pipe_b의 쓰기를 닫아줘야함
			close(pipe_b[1]);
		if (cmd_arg->next == 0)	// 마지막 명령어의 경우 pipe_a가 필요없음
		{
			close(pipe_a[0]);
			close(pipe_a[1]);
		}
	}
	else	// 인덱스 홀수인 경우
	{
		pipe(pipe_b);
		close(pipe_a[1]);	// pipe_a의 쓰기를 닫아줌
		if (cmd_arg->next == 0)	// 마지막 명령어의 경우 pipe_b가 필요없음
		{
			close(pipe_b[0]);
			close(pipe_b[1]);
		}
	}
}

void	chile_process(t_cmd *cmd_arg, int *pipe_a, int *pipe_b)
{
	int	read_fd;
	int	write_fd;

	if (cmd_arg->idx % 2 == 0)	// 명령어의 인덱스가 짝수인 경우에
	{
		read_fd = pipe_b[0];
		write_fd = pipe_a[1];
	}
	else	// 명령어의 인덱스가 홀수인 경우에
	{
		read_fd = pipe_a[0];
		write_fd = pipe_b[1];
	}
	if (cmd_arg->idx == 0)	// 처음 실행되는 명령어
	{
		read_fd = 0;
	}
	else if (cmd_arg->next == 0)	// 마지막으로 실행되는 명령어
	{
		write_fd = 1;
	}
	run_execve(cmd_arg, read_fd, write_fd);	// 명령어 실행
}

void	test_pipex(t_cmd *head, int input_fd, int output_fd)
{
	t_cmd	*parser;
	int		pipe_a[2];	// (마지막이 아닌)짝수인 경우에 쓰기, 홀수인 경우에 읽기
	int		pipe_b[2];	// (마지막이 아닌)홀수인 경우에 쓰기, (처음이 아닌)짝수인 경우에 읽기

	parser = head;
	while (parser)
	{
		connect_redirect(parser, pipe_a, pipe_b);	// 파이프를 리다이렉트 시켜줌
		parser->pid = fork();
		if (!parser->pid)
			chile_process(parser, pipe_a, pipe_b);	// 자식 프로세스에서 명령어 실행
		waitpid(parser->pid, &(parser->status), WNOWAIT);	// 비동기 형식으로 진행, 좀비 프로세스를 방지
		parser = parser->next;
	}
	waitpid(head->pid, &(head->status),0);
}


int	main(int argc, char **argv, char **envp)
{
	t_cmd	*head;
	int	input_fd;
	int	output_fd;

	(void)argc;
	input_fd = 0;
	output_fd = 1;

	set_pipex(argv+1, &head, envp);
	test_pipex(head, input_fd, output_fd);
	//here_doc("eof", 0, 1);
	return (0);
}
