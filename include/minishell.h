/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:12:00 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/01 19:18:55 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>

# include <pipex.h>

# include "../Libft/libft.h"

typedef struct s_state
{
	char	**envp;
}	t_state;

extern t_state	g_state;

void	cpy_env(char **env);
int		two_ptr_counter(char **env);
void	print_prompt(void);
void	ft_echo(char *s);
void	ft_cd(char *s);
void	ft_pwd(void);
void	ft_export(char *s);
void	ft_unset(char *s);
void	ft_env(void);
void	ft_exit(void);

#endif
