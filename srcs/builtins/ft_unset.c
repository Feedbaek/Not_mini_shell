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

static void	del_env(char **env, int idx)
{
	int		i;
	char	**temp;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * two_ptr_counter(env));
	while (*env)
	{
		if (i != idx)
		{
			temp[i] = *env;
			i++;
		}
		env++;
	}
	temp[i] = NULL;
	free(g_state.envp);
	g_state.envp = temp;
}

void	ft_unset(char *s)
{
	int	i;

	i = 0;
	ft_strlcat(s, "=", ft_strlen(s) + 1);
	ft_putendl_fd(s, 1);
	while (g_state.envp[i])
	{
		if (!ft_strncmp(g_state.envp[i], s, ft_strlen(s)))
		{
			del_env(g_state.envp, i);
			break ;
		}
		i++;
	}
}
