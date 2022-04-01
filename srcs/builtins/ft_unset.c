/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:25:35 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/01 19:50:27 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	del_env(int idx)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = 0;
	temp = (char **)malloc(sizeof(char *) * two_ptr_counter(g_state.envp));
	if (!temp)
		malloc_error();
	while (g_state.envp[i])
	{
		if (i != idx)
		{
			temp[j] = g_state.envp[i];
			j++;
		}
		i++;
	}
	temp[j] = NULL;
	free(g_state.envp);
	g_state.envp = temp;
}

void	ft_unset(char **s)
{
	int	i;

	i = 1;
	g_state.exit_status = 0;
	while (s[i])
	{
		if (get_envp_idx(g_state.envp, s[i]) > -1)
			del_env(get_envp_idx(g_state.envp, s[i]));
		i++;
	}
}
