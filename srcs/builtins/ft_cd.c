/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:48:56 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/24 22:42:18 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_cd_error(char *s, char *err)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
	g_state.exit_status = 1;
}

int	get_envp_idx(char **envp, char *s)
{
	int		i;
	char	**temp;

	i = 0;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		if (!temp)
			malloc_error();
		if (equals(temp[0], s))
			return (i);
		i++;
	}
	return (-1);
}

static void	store_pwd(char *s)
{
	char	*val;

	if (!s)
	{
		s = getcwd(s, BUFSIZ);
		val = ft_strjoin("PWD=", s);
		free(s);
	}
	else
		val = ft_strjoin("PWD=", s);
	do_export("PWD", val);
	free(val);
}

void	ft_cd(char **s)
{
	int		home_idx;

	g_state.exit_status = 0;
	home_idx = get_envp_idx(g_state.envp, "HOME");
	if (s[1])
	{
		if (chdir(s[1]) == -1)
			print_cd_error(s[1], strerror(errno));
		else
			store_pwd(NULL);
	}
	else
	{
		if (home_idx < 0)
			print_cd_error("HOME", "HOME not set");
		else
		{
			if (chdir(g_state.envp[home_idx]) == -1)
				print_cd_error("HOME", strerror(errno));
			store_pwd(g_state.envp[home_idx]);
		}
	}
}
