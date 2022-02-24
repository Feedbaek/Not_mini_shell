/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:12:00 by minskim2          #+#    #+#             */
/*   Updated: 2022/02/23 14:30:45 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/errno.h>

# include "../Libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*cpy_env(char **env);
void	print_prompt(t_env *env);
void	ft_echo(char *s);
void	ft_cd(char *s);
void	ft_pwd(void);
void	ft_export(t_env *env, char *s);
void	ft_unset(t_env *env, char *s);
void	ft_env(t_env *env);
void	ft_exit(void);

#endif
