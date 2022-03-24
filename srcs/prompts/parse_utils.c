/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:00:37 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/24 16:09:45 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_fd(int mode, char **src, char **dst, char **t_f)
{
	int	fd;

	if (mode == 2 || mode == 4)
	{
		fd = open(*dst, O_CREAT, 0644);
		close(fd);
	}
	if (*src)
		free(*src);
	*src = *dst;
	free(*t_f);
	return (1);
}

char	**add_arg(char **av, char **arg)
{
	int		i;
	int		len;
	char	**res;

	i = -1;
	len = two_ptr_counter(av);
	res = (char **)malloc(sizeof(char *) * (len + 2));
	if (!res)
		malloc_error();
	while (++i < len)
		res[i] = av[i];
	res[i++] = *arg;
	res[i] = NULL;
	return (res);
}

void	init_struct(t_cmd **x)
{
	t_cmd	*temp;

	temp = *x;
	temp->idx = 0;
	temp->pid = 0;
	temp->status = 0;
	temp->cmd = NULL;
	temp->argv = NULL;
	temp->path = NULL;
	temp->envp = NULL;
	temp->limiter = NULL;
	temp->file = NULL;
	temp->redirect_in = NULL;
	temp->redirect_out = NULL;
	temp->redirect_out_add = NULL;
	temp->next = NULL;
}

static char	*three_strjoin(char *s1, char *s2, char *s3)
{
	char	*rslt;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	rslt = (char *)malloc(s1_len + s2_len + s3_len + 1);
	if (!rslt)
		return (NULL);
	ft_strlcpy(rslt, s1, s1_len + 1);
	ft_strlcat(rslt, s2, s1_len + s2_len + 1);
	ft_strlcat(rslt, s3, s1_len + s2_len + s3_len + 1);
	return (rslt);
}

char	*get_cmd(char *s)
{
	int			i;
	char		*res;
	struct stat	stats;

	i = -1;
	while (g_state.path[++i])
	{
		res = three_strjoin(g_state.path[i], "/", s);
		if (!res)
			malloc_error();
		if (stat(res, &stats) == 0)
			return (res);
		else
			free(res);
	}
	return (ft_strdup(s));
}
