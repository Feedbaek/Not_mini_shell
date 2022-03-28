/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:47:23 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/26 15:51:39 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_t_opt(char *s)
{
	if (ft_strncmp(s, "-n", ft_strlen(s)))
		return (0);
	else
		return (1);
}

void	ft_echo(char **s)
{
	int	t_opt;

	t_opt = check_t_opt(*(s + 1));
	if (t_opt)
		s = s + 2;
	else
		s = s + 1;
	while (*s)
	{
		ft_putstr_fd(*s, 1);
		if (s + 1)
			ft_putchar_fd(' ', 1);
		s++;
	}
	if (!t_opt)
		ft_putchar_fd('\n', 1);
}
