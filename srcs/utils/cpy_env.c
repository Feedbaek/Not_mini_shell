/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:30:20 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/01 19:21:29 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	two_ptr_counter(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

void	cpy_env(char **env)
{
	int		i;
	int		level;

	i = 0;
	g_state.envp = (char **)malloc(sizeof(char *) * (two_ptr_counter(env) + 1));
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
			g_state.path = ft_split(env[i] + 5, ':');
		if (!ft_strncmp("PWD=", env[i], 4))
			g_state.pwd_idx = i;
		if (!ft_strncmp("SHLVL=", env[i], 6))
		{
			level = ft_atoi(env[i] + 6) + 1;
			g_state.envp[i] = ft_strjoin("SHLVL=", ft_itoa(level));
		}
		else
			g_state.envp[i] = ft_strdup(env[i]);
		i++;
	}
	g_state.envp[i] = NULL;
}
