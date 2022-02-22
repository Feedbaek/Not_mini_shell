/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:09:11 by minskim2          #+#    #+#             */
/*   Updated: 2022/02/22 16:23:20 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define  PIPEX_H

# include <minishell.h>

typedef	struct	s_pipe
{
	int	pipe[2];
	pid_t	pid;
	int	status;
}				t_pipe;

int	pipex(void);

#endif
