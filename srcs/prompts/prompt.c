/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:47:43 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/11 15:27:40 by sungmcho         ###   ########.fr       */
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

static int	checker_back_col(char *s)
{
	int	back;

	back = 0;
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
	char		*str;

	while (1)
	{
		ft_putendl_fd("start bash on prompt func\n", 1);
		str = readline("bash $ ");
		if (str)
		{
			if (!checker_back_col(str) && !checker_quote(str) && \
			ft_strncmp(str, "\n", ft_strlen(str)))
				parser(str);
			if (ft_strncmp(str, "\n", ft_strlen(str)))
				add_history(str);
			free(str);
		}
		else
			break ;
	}
}
