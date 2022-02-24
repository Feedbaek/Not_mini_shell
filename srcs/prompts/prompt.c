/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:47:43 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/22 16:20:40 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static char	*find_path(char *cmd)
// {
// 	char	*res;
// 	char	**path_env;
// 	char	*path;

// 	path = getenv("PATH");
// 	path_env =  ft_split(path, ':');
// 	while (*path_env)
// 	{
// 		res = ft_strjoin(*path_env, ft_strjoin("/", cmd));
// 		if (access(res, X_OK) == 0)
// 			return (res);
// 		path_env++;
// 	}
// 	return (res);
// }

static void	parser(char *s, char **env)
{
	while (*s == ' ')
		s++;
	if (!ft_strncmp(s, "echo", 4))
		ft_echo(s + 4);
	else if (!ft_strncmp(s, "cd", 2))
		ft_cd(s + 2);
	else if (!ft_strncmp(s, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(s, "env", 3))
		ft_env(env);
	else if (!ft_strncmp(s, "exit", 4))
		ft_exit();
	else
		ft_putendl_fd(s, 1);
}

void	print_prompt(char **env)
{
	char	*str;

	while (1)
	{
		str = readline("bash $ ");
		if (str)
			parser(str, env);
		else
		{
			printf("exit\n");
			break ;
		}
		add_history(str);
		free(str);
	}
}
