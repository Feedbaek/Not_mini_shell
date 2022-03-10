/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:10:14 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/10 17:35:55 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cmd_init(char **av, t_cmd *x, char **envp);
static void	set_pipex(char ***cmds, t_cmd **head, char **envp, int len);
void	run_execve(t_cmd *cmd_arg, int prev_fd);
void	cmd_process(t_cmd *cmd_arg, int pipe_read, int pipe_write);
void	test_pipex(t_cmd **head, int input_fd, int output_fd);

static int	set_dlm(char prev, char *de, int word_in)
{
	if (!word_in)
	{
		if (!prev)
			*de = ' ';
		else
			*de = prev;
	}
	return (1);
}

static int	count_chunk(char *s)
{
	int		counts;
	int		word_in;
	char	delimiter;

	counts = 0;
	word_in = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '"' || *s == ' ')
		{
			if ((*s == delimiter) && word_in)
			{
				word_in = 0;
				counts++;
			}
		}
		else
			word_in = set_dlm(*(s - 1), &delimiter, word_in);
		s++;
	}
	if (word_in)
		counts++;
	return (counts);
}

static char	*str_processer(char *s, char *b_p, char delimiter)
{
	char	*res;
	char	*temp;

	res = (char *)malloc(s - b_p + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, b_p, (size_t)(s - b_p + 1));
	if (delimiter != '\'')
	{
		temp = process_env_var(res);
		free(res);
		res = temp;
	}
	return (res);
}

static char	**cmd_spliter(char *s)
{
	int		i;
	char	**res;
	char	delimiter;
	char	*b_p;

	i = 0;
	res = (char **)malloc((count_chunk(s) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (*s)
	{
		if (*s != '\'' && *s != '"' && *s != ' ')
		{
			b_p = s;
			set_dlm(*(s - 1), &delimiter, 0);
			while (*s && *s != delimiter)
				++s;
			res[i] = str_processer(s, b_p, delimiter);
			if (!res[i++])
				return (d_ret_null(&res));
		}
		s++;
	}
	res[i] = NULL;
	return (res);
}

void	parser(char *s)
{
	char	**res;
	char	**temp;
	char	***cmds;
	int		i;
	t_cmd	*head;

	i = -1;
	temp = ft_split(s, '|');
	cmds = (char ***)malloc(sizeof(char **) * (two_ptr_counter(temp) + 1));
	if (temp && cmds)
	{
		while (temp[++i])
		{
			res = cmd_spliter(temp[i]);
			if (!res)
				break ;
			cmds[i] = res;
		}
		set_pipex(cmds, &head, g_state.envp, two_ptr_counter(temp));
		test_pipex(&head, 0, 1);
	}
}

// custom pipex 구간입니다.


static int	test_path_split(char **envp, t_cmd *x)
{
	char	*path;
	char	*tmp;
	char	**parser;

	while (*envp && minskim2_strncmp(*envp, "PATH", 4))
		envp++;
	if (!(*envp))
		return (0);
	path = *envp;
	x->path = minskim2_split(path + 5, ':');
	if (!(x->path))
		return (0);
	parser = x->path;
	while (*parser)
	{
		tmp = *parser;
		*parser = minskim2_strjoin(*parser, "/");
		if (!*parser)
			return (0);
		parser++;
		free(tmp);
	}
	return (1);
}

static int	test_path_finder(char **envp, t_cmd *x, char*split)
{
	int		mode;
	char	**parser;

	mode = F_OK | X_OK;
	if (!test_path_split(envp, x))
		return (0);
	parser = x->path;
	while (*parser)
	{
		x->cmd = minskim2_strjoin(*parser, split);
		if (!x->cmd)
			return (0);
		if (!access(x->cmd, mode))
			return (1);
		free(x->cmd);
		parser++;
	}
	return (0);
}

static void	cmd_init(char **av, t_cmd *x, char **envp)
{
	if (!test_path_finder(envp, x, av[0]))
	{
		printf("init error: %s\n", strerror(errno));
		exit(1);
	}
	x->argv = av;
	x->envp = envp;
	x->next = 0;
}

static void	set_pipex(char ***cmds, t_cmd **head, char **envp, int len)
{
	int		i;
	t_cmd	*cmd_arg;
	t_cmd	*prev_cmd;

	i = 0;
	while (i < len)
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
		cmd_init(cmds[i], cmd_arg, envp);
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

void	cmd_process(t_cmd *cmd_arg, int pipe_read, int pipe_write)
{
	dup2(pipe_read, STDIN_FILENO);
	dup2(pipe_write, STDOUT_FILENO);
	if (execve(cmd_arg->cmd, cmd_arg->argv, cmd_arg->envp) == -1)
	{
		printf("run_execve error: %s\n", strerror(errno));
		exit(1);
	}
}

//void	reconnect_pipe(t_cmd *cmd_arg)
//{

//}

void	test_pipex(t_cmd **head, int input_fd, int output_fd)
{
	t_cmd	*parser;
	int		pipe_a[2];
	int		pipe_b[2];
	int		read_fd;
	int		write_fd;

	parser = *head;
	while (parser)
	{
		if (parser->idx % 2 == 0)	// 인덱스 짝수의 경우
		{
			pipe(pipe_a);
			if (parser->idx != 0)
				close(pipe_b[1]);
			if (parser->next == 0)
				close(pipe_a[1]);
		}
		else
		{
			pipe(pipe_b);
			close(pipe_a[1]);
			if (parser->next == 0)
				close(pipe_b[1]);
		}
		parser->pid = fork();
		if (!parser->pid)
		{
			if (parser->idx % 2 == 0)
			{
				read_fd = pipe_b[0];
				write_fd = pipe_a[1];
			}
			else
			{
				read_fd = pipe_a[0];
				write_fd = pipe_b[1];
			}
			if (parser->idx == 0)
				read_fd = input_fd;
			else if (parser->next == 0)
				write_fd = output_fd;
			cmd_process(parser, read_fd, write_fd);
		}
		waitpid(parser->pid, &(parser->status), WNOWAIT);
		parser = parser->next;
	}
	waitpid((*head)->pid, &((*head)->status),0);
}
