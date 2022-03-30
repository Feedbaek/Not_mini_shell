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
# include <termios.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include <pipex.h>
# include <get_next_line.h>

# include "../Libft/libft.h"

typedef struct s_state
{
	char	**envp;
	char	**path;
	int		exit_status;
	int		pwd_idx;
}	t_state;

typedef struct s_parsed
{
	char	de;
	char	*token;
}	t_parsed;

extern t_state	g_state;

void	ft_echo(char **s);
void	ft_cd(char **s);
void	ft_pwd(void);
void	ft_export(char **s);
void	ft_unset(char **s);
void	ft_env(void);
void	ft_exit(char **s);

void	cpy_env(char **env);
void	handle_signal(int signo);

int		two_ptr_counter(char **env);
void	free_double_pointer(char ***tab);
char	*one_ret_null(char **s);
char	**d_ret_null(char ***s);
void	malloc_error(void);

void	echoctl_on(void);
void	echoctl_off(void);

void	print_prompt(void);
void	parser(char *s, t_cmd **head);
char	*process_env_var(char *s);
void	tokenize_line(char **split, t_parsed **parsed);
int		set_fd(int mode, char **src, char **dst, char **t_f);
char	**add_arg(char **av, char **arg);
void	init_struct(t_cmd **x);
char	*get_cmd(char *s);
void	execute_func(t_cmd	*head);

#endif
