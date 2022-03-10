/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:59:34 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/10 14:14:54 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*find_env_var(char *s)
{
	int		i;
	int		len;
	char	**temp;
	char	*res;

	i = -1;
	len = ft_strlen(s);
	while (g_state.envp[++i])
	{
		temp = ft_split(g_state.envp[i], '=');
		if (!temp)
			return (NULL);
		if (ft_strlen(temp[0]) > ft_strlen(s))
			len = ft_strlen(temp[0]);
		if (!ft_strncmp(temp[0], s, len))
		{
			res = temp[1];
			free(temp[0]);
			free(temp);
			return (res);
		}
		free_double_pointer(temp);
	}
	return (ft_strdup(""));
}

static char	*join_env_value(char *s, char *s_c_addr)
{
	char	*res;
	char	*env_k;
	char	*env_v;
	int		i;

	i = 0;
	while (s_c_addr[i] && s_c_addr[i] != ' ')
		i++;
	env_k = (char *)malloc(i);
	if (!env_k)
		return (NULL);
	ft_strlcpy(env_k, s_c_addr, i);
	env_v = find_env_var(env_k);
	if (!env_v)
		return (NULL);
	res = (char *)malloc(ft_strlen(s) + ft_strlen(env_v) + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, s_c_addr - s);
	ft_strlcat(res, env_v, ft_strlen(res) + ft_strlen(env_v) + 1);
	ft_strlcat(res, s_c_addr + i, ft_strlen(s) + ft_strlen(env_v) + 1);
	free(env_k);
	free(env_v);
	return (res);
}

char	*process_env_var(char *s)
{
	char	*s_c_addr;
	char	*res;
	char	*temp;

	res = ft_strdup(s);
	while (1)
	{
		s_c_addr = ft_strchr(res, '$');
		if (s_c_addr)
		{
			temp = res;
			res = join_env_value(res, s_c_addr + 1);
			if (!res)
				return (NULL);
			free(temp);
		}
		else
			break ;
	}
	return (res);
}
