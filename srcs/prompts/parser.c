/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:10:14 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/11 16:08:26 by sungmcho         ###   ########.fr       */
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
