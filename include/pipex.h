/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:09:11 by minskim2          #+#    #+#             */
/*   Updated: 2022/02/22 16:58:27 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define  PIPEX_H

# include <minishell.h>

typedef	struct	s_cmd
{
	int		pipe[2];
	pid_t	pid;
	int		status;
	char	*cmd;
	char	**argv;
	char	**path;
}				t_cmd;

int	pipex(char **argv, char **envp);

#endif
