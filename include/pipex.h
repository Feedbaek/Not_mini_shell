/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:09:11 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/01 21:03:00 by minskim2         ###   ########.fr       */
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
	char	**envp;
	struct s_cmd	*next;
}				t_cmd;

int		pipex(char **argv, char **envp);
int		minskim2_strncmp(const char *s1, const char *s2, size_t n);
size_t	minskim2_strlen(const char *str);
void	redirect_in(const char *file);
void	redirect_out(const char *file);
int		path_finder(char **envp, t_cmd *x, char*split);
char	*minskim2_strjoin(char const *s1, char const *s2);
char	**minskim2_split(char const *s, char c);

#endif
