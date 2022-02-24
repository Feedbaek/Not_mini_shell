/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:48:56 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/22 16:24:24 by minskim2         ###   ########.fr       */
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
		chdir("..");
	else
		chdir(s + i);
}
