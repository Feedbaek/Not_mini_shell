/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:10:14 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/15 15:14:06 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <pipex.h>

static int	check_token(char *s1, char *s2, char de, t_cmd *x)
{
	if (ft_strlen(s1) == 1 && de == ' ')
	{
		if (*s1 == '<')
			return (set_fd(1, &(x->redirect_in), &s2, &s1));
		if (*s1 == '>')
			return (set_fd(2, &(x->redirect_out), &s2, &s1));
	}
	if (ft_strlen(s1) == 2 && de == ' ')
	{
		if (!ft_strncmp(s1, "<<", 2))
			return (set_fd(3, &(x->limiter), &s2, &s1));
		if (!ft_strncmp(s1, ">>", 2))
			return (set_fd(4, &(x->redirect_out_add), &s2, &s1));
	}
	return (0);
}

void	add_cmd(t_cmd *x, char **s)
{
	char	**temp;

	if (x->argv)
	{
		temp = x->argv;
		x->argv = add_arg(x->argv, s);
		free(temp);
	}
	else
	{
		x->argv = (char **)malloc(sizeof(char *) * 2);
		if (!x->argv)
			malloc_error();
		x->argv[0] = *s;
		x->argv[1] = NULL;
		x->cmd = *s;
	}
}

static void	cmd_init(t_parsed *parsed, t_cmd *x)
{
	int	i;
	int	ret;

	i = -1;
	x->limiter = NULL;
	x->redirect_in = NULL;
	x->redirect_out = NULL;
	x->redirect_out_add = NULL;
	x->argv = NULL;
	while (parsed[++i].token)
	{
		ret = check_token(parsed[i].token, parsed[i + 1].token, \
						parsed[i].de, x);
		if (ret > 0)
		{
			i += ret;
			continue ;
		}
		else
			add_cmd(x, &parsed[i].token);
	}
	x->next = 0;
}

static void	set_cmds(t_parsed **tokenized, int len, t_cmd **head)
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
		else
		{
			prev_cmd->next = cmd_arg;
			prev_cmd = cmd_arg;
		}
		cmd_init(tokenized[i], cmd_arg);
		cmd_arg->idx = i;
		i++;
	}
}

void	parser(char *s, t_cmd **head)
{
	int			i;
	int			len;
	char		**splited_w_vb;
	t_parsed	**tokenized;

	splited_w_vb = ft_split(s, '|');
	if (!splited_w_vb)
		malloc_error();
	len = two_ptr_counter(splited_w_vb);
	tokenized = (t_parsed **)malloc(sizeof(t_parsed *) * (len + 1));
	if (!tokenized)
		malloc_error();
	tokenized[len] = NULL;
	tokenize_line(splited_w_vb, tokenized);
	set_cmds(tokenized, len, head);
	i = -1;
	while (++i < len)
		free(tokenized[i]);
	free(tokenized);
}
