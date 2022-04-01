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
	int		i;
	int		len;
	char	**tmp;

	i = -1;
	len = two_ptr_counter(g_state.envp);
	tmp = (char **)malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		malloc_error();
	while (g_state.envp[++i])
		tmp[i] = g_state.envp[i];
	tmp[i++] = ft_strdup(s);
	tmp[i] = NULL;
	free(g_state.envp);
	g_state.envp = tmp;
}

void	do_export(char *k, char *s)
{
	int	idx;

	idx = get_envp_idx(g_state.envp, k);
	if (idx < 0)
		add_envp(s);
	else
	{
		free(g_state.envp[idx]);
		g_state.envp[idx] = ft_strdup(s);
	}
}

static int	check_validity(char *s, char *export)
{
	if (*s != '_' && !ft_isalpha(*s))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(export, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (0);
	}
	while (*(++s))
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
			if (two_ptr_counter(split) > 1)
			{
				if (!check_validity(split[0], s[i]) \
					|| !check_validity(split[1], s[i]))
					break ;
				if (!split)
					malloc_error();
				if (split[1])
					do_export(split[0], s[i]);
				free_double_pointer(&split);
			}
			i++;
		}
	}
	g_state.exit_status = 0;
}
