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

int	two_ptr_counter(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	cpy_env(char **env)
{
	int	i;

	i = 0;
	g_state.envp = (char **)malloc(sizeof(char *) * (two_ptr_counter(env) + 1));
	while (env[i])
	{
		g_state.envp[i] = ft_strdup(env[i]);
		i++;
	}
	g_state.envp[i] = NULL;
}
