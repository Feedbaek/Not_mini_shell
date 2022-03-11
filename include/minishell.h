/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:12:00 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/11 16:02:12 by sungmcho         ###   ########.fr       */
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
	int		exit_status;
}	t_state;

extern t_state	g_state;

void	ft_echo(char *s);
void	ft_cd(char *s);
void	ft_pwd(void);
void	ft_export(char *s);
void	ft_unset(char *s);
void	ft_env(void);
void	ft_exit(void);
void	cpy_env(char **env);
void	handle_signal(int signo);
void	handle_signal2(int signo);
int		two_ptr_counter(char **env);
void	print_prompt(void);
void	parser(char *s);
void	free_double_pointer(char ***tab);
char	*one_ret_null(char **s);
char	**d_ret_null(char ***s);
char	*process_env_var(char *s);

#endif
