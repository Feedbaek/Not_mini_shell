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

static int	lprint(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
	{
		ft_putchar_fd(s[i], 1);
		i++;
	}
	return (i);
}

static void	print_env(void)
{
	int	i;
	int	len;

	i = -1;
	while (g_state.envp[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		len = lprint(g_state.envp[i]);
		ft_putchar_fd('=', 1);
		ft_putchar_fd('\"', 1);
		ft_putstr_fd(g_state.envp[i] + len, 1);
		ft_putstr_fd("\"\n", 1);
	}
}

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

void	ft_export(char **s)
{
	char	**temp;
	int		len;

	if (*(s + 1))
	{
		len = two_ptr_counter(g_state.envp);
		temp = cpy(g_state.envp, len);
		temp[len] = ft_strdup(s[1]);
		temp[len + 1] = NULL;
		free(g_state.envp);
		g_state.envp = temp;
	}
	else
		print_env();
}
