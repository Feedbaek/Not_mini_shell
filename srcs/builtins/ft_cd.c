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

void	ft_cd(char *s)
{
	char	*pwd;

	pwd = NULL;
	if (chdir(s) == -1)
		printf("cd: %s: %s\n", s, strerror(errno));
	else
	{
		pwd = getcwd(pwd, BUFSIZ);
		free(g_state.envp[g_state.pwd_idx]);
		g_state.envp[g_state.pwd_idx] = ft_strjoin("PWD=", pwd);
		free(pwd);
	}
}
