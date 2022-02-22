/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:48:56 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/22 00:56:07 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
