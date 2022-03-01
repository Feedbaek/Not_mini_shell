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

static char	**cpy(char **env, int len)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (len + 2));
	while (env[i])
	{
		res[i] = env[i];
		i++;
	}
	return (res);
}

void	ft_export(char *s)
{
	char	**temp;
	int		len;

	len = two_ptr_counter(g_state.envp);
	temp = cpy(g_state.envp, len);
	temp[len] = ft_strdup(s);
	temp[len + 1] = NULL;
	free(g_state.envp);
	g_state.envp = temp;
}
