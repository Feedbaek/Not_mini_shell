/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:59:34 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/09 16:01:26 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*find_env_var(char *s, int len)
{
	int		i;
	int		len;
	char	**temp;
	char	*res;

	i = -1;
	s[i] = '\0';
	len = ft_strlen(s);
	while (g_state.envp[++i])
	{
		temp = ft_split(g_state.envp[i], "=");
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

char	*process_env_var(char *s)
{
	char	*var_loc;
	char	*temp;
	char	*res;
	char	*env_val;
	int		i;

	while (1)
	{
		var_loc = ft_strchr(s, '$');
		if (!var_loc)
			break ;
		temp = (char *)malloc(var_loc - s + 1);
		if (!temp)
			return (NULL);
		ft_strlcpy(temp, s, var_loc - s + 1);
		i = 0;
		while (!s[i] && s[i] != ' ')
			i++;
		env_val = find_env_var(var_loc, i);
		res = ft_strjoin(temp, env_val);
		free(temp);
		if (env_val)
			free(env_val);
		s = var_loc + i;
	}
	return (res);
}
