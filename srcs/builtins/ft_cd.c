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
}

void	ft_cd(char **s)
{
	char	*pwd;

	pwd = NULL;
	if (s[1])
	{
		if (chdir(s[1]) == -1)
			print_cd_error(s[1], strerror(errno));
		else
		{
			pwd = getcwd(pwd, BUFSIZ);
			free(g_state.envp[g_state.pwd_idx]);
			g_state.envp[g_state.pwd_idx] = ft_strjoin("PWD=", pwd);
			free(pwd);
		}
	}
	else
	{
		if (chdir(getenv("HOME")) == -1)
			print_cd_error(s[1], strerror(errno));
		g_state.envp[g_state.pwd_idx] = ft_strjoin("PWD=", getenv("HOME"));
	}
}
