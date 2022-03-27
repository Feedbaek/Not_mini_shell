/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:53:38 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/27 17:17:38 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	connect_stdin(t_cmd *cmd_arg, int pipe_read, int pipe_write)
{
	int fd;

	if (cmd_arg->limiter)			// << 가 있으면
	{
		fd = open(cmd_arg->tmp, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (cmd_arg->redirect_in)		// < 가 있으면
	{
		redirect_in(cmd_arg->redirect_in, STDIN_FILENO);
	}
	else {		// < 가  없으면
		dup2(pipe_read, STDIN_FILENO);
	}
}

static void	connect_stdout(t_cmd *cmd_arg, int pipe_read, int pipe_write)
{
	if (cmd_arg->redirect_out_add)	// >> 가  있으면
	{
		redirect_out_add(cmd_arg->redirect_out_add, STDOUT_FILENO);
		if (pipe_write != STDOUT_FILENO)
			close(pipe_write);
	}
	else if (cmd_arg->redirect_out)	// > 가  있으면
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
		read_fd = STDIN_FILENO;
	if (cmd_arg->next == 0)	// 마지막으로 실행되는 명령어
		write_fd = STDOUT_FILENO;
	connect_stdin(cmd_arg, read_fd, write_fd);	// 표준입력 리다이렉트
	connect_stdout(cmd_arg, read_fd, write_fd);	// 표준출력 리다이렉트
	run_execve(cmd_arg, "run_execve error");	// 명령어 실행
}

void	disconnect_redirect(t_cmd *cmd_arg, int *pipe_a, int *pipe_b)
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
	else	// 인덱스 홀수인 경우 처음 명령어일 수는 없음
	{
		pipe(pipe_b);
		close(pipe_a[1]);	// 안쓰는 pipe_a의 쓰기를 닫아줌
		if (cmd_arg->next == 0)		// 마지막 명령어의 경우
		{
			close(pipe_b[0]);
			close(pipe_b[1]);
		}
	}
}

void	test_pipex(t_cmd *head)
{
	t_cmd	*parser;
	int		pipe_a[2];	// (마지막이 아닌)짝수인 경우에 쓰기, 홀수인 경우에 읽기
	int		pipe_b[2];	// (마지막이 아닌)홀수인 경우에 쓰기, (처음이 아닌)짝수인 경우에 읽기
	int		i;

	//printf("test_pipex start\n");
	here_doc(head);		// 명령어들을 실행하기 전에 한번 here_doc으로 임시파일들을 만들어줌
	parser = head;
	while (parser && parser->cmd)
	{
		disconnect_redirect(parser, pipe_a, pipe_b);	// 파이프를 리다이렉트 시켜줌
		parser->pid = fork();
		if (!parser->pid)
			child_process(parser, pipe_a, pipe_b);	// 자식 프로세스에서 명령어 실행
		parser = parser->next;
	}
	wait_pid(head);
	//printf("test_pipex end\n");
}


//int	main(int argc, char **argv, char **envp)
//{
//	t_cmd	*head;
//	int	input_fd;
//	int	output_fd;

//	(void)argc;
//	input_fd = 0;
//	output_fd = 1;

//	set_pipex(argv+1, &head, envp);
//	test_pipex(head);
//	return (0);
//}
