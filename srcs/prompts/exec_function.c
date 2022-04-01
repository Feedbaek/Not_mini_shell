/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:12:31 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/30 17:12:34 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_func(t_cmd	*head)
{
	if (equals(head->argv[0], "echo"))
		ft_echo(head->argv);
	else if (equals(head->argv[0], "cd"))
		ft_cd(head->argv);
	else if (equals(head->argv[0], "pwd"))
		ft_pwd();
	else if (equals(head->argv[0], "export"))
		ft_export(head->argv);
	else if (equals(head->argv[0], "unset"))
		ft_unset(head->argv);
	else if (equals(head->argv[0], "env"))
		ft_env();
	else if (equals(head->argv[0], "exit"))
		ft_exit(head->argv);
	// if (head->cmd && *head->cmd)
	// {
	// 	if (!ft_strncmp(head->cmd, "echo", 4) && ft_strlen(head->cmd) == 4)
	// 		ft_echo(head->argv);
	// 	else if (!ft_strncmp(head->cmd, "cd", 2) && ft_strlen(head->cmd) == 2)
	// 		ft_cd(head->argv);
	// 	else if (!ft_strncmp(head->cmd, "pwd", 3) && ft_strlen(head->cmd) == 3)
	// 		ft_pwd();
	// 	else if (!ft_strncmp(head->cmd, "export", 6) \
	// 			&& ft_strlen(head->cmd) == 6)
	// 		ft_export(head->argv);
	// 	else if (!ft_strncmp(head->cmd, "unset", 5) \
	// 			&& ft_strlen(head->cmd) == 5)
	// 		ft_unset(head->argv);
	// 	else if (!ft_strncmp(head->cmd, "env", 3) && ft_strlen(head->cmd) == 3)
	// 		ft_env();
	// 	else if (!ft_strncmp(head->cmd, "exit", 4) && ft_strlen(head->cmd) == 4)
	// 		ft_exit(head->argv);
	// 	else
	// 	{
	// 		echoctl_on();
	// 		test_pipex(head);
	// 		echoctl_off();
	// 	}
	// }
}
