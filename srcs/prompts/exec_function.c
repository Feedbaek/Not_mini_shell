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
	if (head->cmd && *head->cmd)
	{
		if (!ft_strncmp(head->cmd, "echo", ft_strlen(head->cmd)))
			ft_echo(head->argv);
		else if (!ft_strncmp(head->cmd, "cd", ft_strlen(head->cmd)))
			ft_cd(head->argv);
		else if (!ft_strncmp(head->cmd, "pwd", ft_strlen(head->cmd)))
			ft_pwd();
		else if (!ft_strncmp(head->cmd, "export", ft_strlen(head->cmd)))
			ft_export(head->argv);
		else if (!ft_strncmp(head->cmd, "unset", ft_strlen(head->cmd)))
			ft_unset(head->argv);
		else if (!ft_strncmp(head->cmd, "env", ft_strlen(head->cmd)))
			ft_env();
		else if (!ft_strncmp(head->cmd, "exit", ft_strlen(head->cmd)))
			ft_exit(head->argv);
		else
		{
			echoctl_on();
			test_pipex(head);
			echoctl_off();
		}
	}
}
