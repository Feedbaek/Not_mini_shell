/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:48:56 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/24 22:42:18 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_cd(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (!ft_strncmp(s + i, "..", ft_strlen(s) - i) && ft_strlen(s) - i == 2)
	{
		if (chdir("..") == -1)
			printf("cd: %s: %s\n", s + i, strerror(errno));
	}
	else
	{
		if (chdir(s + i) == -1)
			printf("cd: %s: %s\n", s + i, strerror(errno));
	}
}
