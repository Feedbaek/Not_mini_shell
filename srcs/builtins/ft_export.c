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

static void	add_envp(char *s)
{
	char	**temp;
	int		len;
	int		i;

	i = 0;
	len = two_ptr_counter(g_state.envp);
	temp = (char **)malloc(len + 2);
	if (!temp)
		malloc_error();
	while (g_state.envp[i])
	{
		temp[i] = ft_strdup(g_state.envp[i]);
		i++;
	}
	temp[i++] = ft_strdup(s);
	temp[i] = NULL;
	free_double_pointer(&g_state.envp);
	g_state.envp = temp;
}

static int	find_env(char *s)
{
	int	i;

	i = 0;
	while (g_state.envp[i])
	{
		if (ft_strncmp(g_state.envp[i], s, ft_strlen(s) + 1) == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	do_export(char *k, char *s)
{
	int	idx;

	idx = find_env(k);
	if (idx < 0)
		add_envp(s);
	else
	{
		free(g_state.envp[idx]);
		g_state.envp[idx] = ft_strdup(s);
	}
}

void	ft_export(char **s)
{
	char	**split;
	int		i;

	i = 1;
	if (two_ptr_counter(s) == 1)
		print_env();
	else
	{
		while (s[i])
		{
			split = ft_split(s[i], '=');
			if (!split)
				malloc_error();
			if (split[1])
				do_export(split[0], s[i]);
			free_double_pointer(&split);
			i++;
		}
	}
	g_state.exit_status = 0;
}
