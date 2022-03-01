/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:47:43 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/01 19:49:50 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	execute_func(char *s)
{
	if (!ft_strncmp(s, "echo", 4))
		ft_echo(s + 4);
	else if (!ft_strncmp(s, "cd", 2))
		ft_cd(s + 2);
	else if (!ft_strncmp(s, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(s, "export", 6))
		ft_export(s + 7);
	else if (!ft_strncmp(s, "unset", 5))
		ft_unset(s + 6);
	else if (!ft_strncmp(s, "env", 3))
		ft_env();
	else if (!ft_strncmp(s, "exit", 4))
		ft_exit();
	else
		ft_putendl_fd(s, 1);
}

static void	parser(char *s)
{
	while (*s == ' ')
		s++;
	execute_func(s);
}

static int	checker(char *s, int c)
{
	int	i;
	int	back;

	i = 0;
	back = 0;
	while (*s)
	{
		if (*s == c)
			i++;
		if (*s == '\\' || *s == ';')
		{
			ft_putendl_fd("We don't interrupt \\ or ;", 1);
			return (1);
		}
		s++;
	}
	if (i % 2 != 0)
	{
		ft_putendl_fd("You have unclosed quotes!", 1);
		return (1);
	}
	return (0);
}

void	print_prompt(void)
{
	char	*str;

	while (1)
	{
		str = readline("bash $ ");
		if (str)
		{
			if (!checker(str, '\'') && !checker(str, '"'))
				parser(str);
		}
		else
			break ;
		if (ft_strncmp(str, "\n", ft_strlen(str)))
			add_history(str);
		free(str);
	}
}
