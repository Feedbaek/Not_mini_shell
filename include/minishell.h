/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:12:00 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/06 19:45:07 by minskim2         ###   ########.fr       */
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
# include <get_next_line.h>

# include "../Libft/libft.h"

# define PIPE_FLAGS 0
# define REDIR_LEFT 1
# define REDIR_RIGHT 2
# define REDIR_APPEN_LEFT 3
# define REDIR_APPEN_RIGHT 4

typedef struct s_state
{
	char	**envp;
	int		in_fd;
	int		out_fd;
}	t_state;

extern t_state	g_state;

void	cpy_env(char **env);
int		two_ptr_counter(char **env);
void	print_prompt(void);
void	parser(char *s);
void	ft_echo(char *s);
void	ft_cd(char *s);
void	ft_pwd(void);
void	ft_export(char *s);
void	ft_unset(char *s);
void	ft_env(void);
void	ft_exit(void);

#endif
