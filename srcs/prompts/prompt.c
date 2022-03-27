/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:47:43 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/28 01:59:45 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	execute_func(t_cmd	*head)
{
	if (!ft_strncmp(head->cmd, "echo", 4))
		ft_echo(head->argv[1]);
	else if (!ft_strncmp(head->cmd, "cd", 2))
		ft_cd(head->argv[1]);
	else if (!ft_strncmp(head->cmd, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(head->cmd, "export", 6))
		ft_export(head->argv[1]);
	else if (!ft_strncmp(head->cmd, "unset", 5))
		ft_unset(head->argv[1]);
	else if (!ft_strncmp(head->cmd, "env", 3))
		ft_env();
	else if (!ft_strncmp(head->cmd, "exit", 4))
		ft_exit();
	else
		test_pipex(head);
}

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
				execute_func(head);
				free_cmds(head);
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
