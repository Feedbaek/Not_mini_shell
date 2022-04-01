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
		if (equals(head->cmd, "echo"))
			ft_echo(head->argv);
		else if (equals(head->cmd, "cd"))
			ft_cd(head->argv);
		else if (equals(head->cmd, "pwd"))
			ft_pwd();
		else if (equals(head->cmd, "export"))
			ft_export(head->argv);
		else if (equals(head->cmd, "unset"))
			ft_unset(head->argv);
		else if (equals(head->cmd, "env"))
			ft_env();
		else if (equals(head->cmd, "exit"))
			ft_exit(head->argv);
		else
		{
			echoctl_on();
			test_pipex(head);
			echoctl_off();
		}
	}
}
