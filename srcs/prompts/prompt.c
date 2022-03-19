/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:47:43 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/15 09:47:48 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static void	execute_func(char *s)
// {
// 	if (!ft_strncmp(s, "echo", 4))
// 		ft_echo(s + 4);
// 	else if (!ft_strncmp(s, "cd", 2))
// 		ft_cd(s + 2);
// 	else if (!ft_strncmp(s, "pwd", 3))
// 		ft_pwd();
// 	else if (!ft_strncmp(s, "export", 6))
// 		ft_export(s + 7);
// 	else if (!ft_strncmp(s, "unset", 5))
// 		ft_unset(s + 6);
// 	else if (!ft_strncmp(s, "env", 3))
// 		ft_env();
// 	else if (!ft_strncmp(s, "exit", 4))
// 		ft_exit();
// 	else
// 		ft_putendl_fd(s, 1);
// }

static void	free_cmds(t_cmd *tab)
{
	t_cmd	*temp;

	while (tab)
	{
		if (tab->cmd)
			free(tab->cmd);
		if (tab->argv)
			free_double_pointer(&tab->argv);
		if (tab->path)
			free_double_pointer(&tab->path);
		if (tab->limiter)
			free(tab->limiter);
		if (tab->file)
			free(tab->file);
		if (tab->redirect_in)
			free(tab->redirect_in);
		if (tab->redirect_out)
			free(tab->redirect_out);
		if (tab->redirect_out_add)
			free(tab->redirect_out_add);
		temp = tab;
		free(tab);
		tab = temp->next;
	}
}

static int	checker_back_col(char *s)
{
	while (*s)
	{
		if (*s == '\\' || *s == ';')
		{
			ft_putendl_fd("We don't interrupt \\ or ;", STDERR_FILENO);
			return (1);
		}
		s++;
	}
	return (0);
}

static int	checker_quote(char *s)
{
	int	num_quotes;
	int	num_dquotes;

	num_quotes = 0;
	num_dquotes = 0;
	while (*s)
	{
		if (*s == '\'')
			num_quotes++;
		if (*s == '"')
			num_dquotes++;
		s++;
	}
	if (num_quotes % 2 != 0 || num_dquotes % 2 != 0)
		return (1);
	return (0);
}

void	print_prompt(void)
{
	char	*str;
	t_cmd	*head;

	while (1)
	{
		str = readline("bash $ ");
		if (str)
		{
			if (!checker_back_col(str) && !checker_quote(str) && \
			ft_strncmp(str, "\n", ft_strlen(str)))
			{
				parser(str, &head);
				t_cmd *tmp = head;
				while (tmp)
				{
					if (tmp->cmd)
						ft_putendl_fd(tmp->cmd, 1);
					if (tmp->redirect_in)
						ft_putendl_fd(tmp->redirect_in, 1);
					if (tmp->redirect_out)
						ft_putendl_fd(tmp->redirect_out, 1);
					if (tmp->redirect_out_add)
						ft_putendl_fd(tmp->redirect_out_add, 1);
					if (tmp->limiter)
						ft_putendl_fd(tmp->limiter, 1);
					while (*(tmp->argv))
					{
						ft_putstr_fd(*(tmp->argv), 1);
						ft_putchar_fd(' ', 1);
						(tmp->argv)++;
					}
					ft_putchar_fd('\n', 1);
					tmp = tmp->next;
				}
				free_cmds(tmp);
			}
			if (ft_strncmp(str, "\n", ft_strlen(str)))
				add_history(str);
			free(str);
			str = NULL;
		}
		else
			break ;
	}
}
