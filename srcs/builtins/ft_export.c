/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:01:03 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/01 19:47:28 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_env(void)
{
	int	i;
	int	len;

	i = -1;
	while (g_state.envp[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(g_state.envp[i], 1);
	}
}

static int	check(char *s, char *export, int i)
{
	if (i)
	{
		if (*s != '_' && !ft_isalpha(*s))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(export, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (0);
		}
		s++;
	}
	while (*(s++))
	{
		if (*s != '_' && !ft_isalnum(*s))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(export, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (0);
		}
	}
	return (1);
}

static int	validate(char **split, char *s)
{
	int	k;
	int	v;

	k = 0;
	v = 1;
	if (split[0])
		k = check(split[0], s, 1);
	if (split[1])
		v = check(split[1], s, 0);
	return (k && v);
}

void	ft_export(char **s)
{
	char	**split;
	int		i;

	i = 0;
	if (two_ptr_counter(s) == 1)
		print_env();
	else
	{
		while (s[++i])
		{
			if (ft_strchr(s[i], '='))
			{
				split = ft_split(s[i], '=');
				if (!split)
					malloc_error();
				if (!validate(split, s[i]))
					break ;
				else
					do_export(split[0], s[i]);
				free_double_pointer(&split);
			}
		}
	}
	g_state.exit_status = 0;
}
