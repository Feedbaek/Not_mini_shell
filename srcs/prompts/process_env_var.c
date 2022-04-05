/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:59:34 by sungmcho          #+#    #+#             */
/*   Updated: 2022/04/05 22:10:09 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_env_var(char *s)
{
	int		i;
	char	**temp;
	char	*res;

	i = -1;
	if (equals(s, "?"))
		return (ft_itoa(g_state.exit_status));
	while (g_state.envp[++i])
	{
		temp = ft_split(g_state.envp[i], '=');
		if (!temp)
			malloc_error();
		if (equals(temp[0], s))
		{
			if (temp[1])
				res = ft_strdup(temp[1]);
			else
				res = ft_strdup("");
			free_double_pointer(&temp);
			return (res);
		}
		free_double_pointer(&temp);
	}
	return (ft_strdup(""));
}

static char	*join_env_value(char *s, char *env_k, char *s_c_addr)
{
	char	*res;
	char	*env_v;

	env_v = find_env_var(env_k);
	if (!env_v)
		return (NULL);
	res = (char *)malloc(ft_strlen(s) + ft_strlen(env_v) - ft_strlen(env_k));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, s_c_addr - s + 1);
	ft_strlcat(res, env_v, ft_strlen(res) + ft_strlen(env_v) + 1);
	ft_strlcat(res, s_c_addr + ft_strlen(env_k) + 1, \
				ft_strlen(res) + ft_strlen(s_c_addr + ft_strlen(env_k) + 1) \
				+ 1);
	free(env_v);
	return (res);
}

static char	*split(char *s)
{
	int		i;
	char	*res;

	i = 0;
	if (equals(s, ""))
		return (ft_strdup("$"));
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
		i++;
	res = (char *)malloc(i);
	if (!res)
		malloc_error();
	ft_strlcpy(res, s, i + 1);
	return (res);
}

void	process_env_var(char **s)
{
	char	*s_c_addr;
	char	*res;
	char	*temp;
	char	*temp2;

	res = ft_strdup(*s);
	free(*s);
	while (1)
	{
		s_c_addr = ft_strchr(res, '$');
		if (s_c_addr)
		{
			temp = split(s_c_addr + 1);
			temp2 = join_env_value(res, temp, s_c_addr);
			free(temp);
			free(res);
			res = temp2;
		}
		else
			break ;
	}
	*s = res;
}
