/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:00:37 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/10 12:06:17 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_fd(int mode, char **src, char **dst, char **t_f)
{
	int	fd;

	if (mode == 2 || mode == 4)
	{
		fd = open(*dst, O_CREAT, 755);
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
