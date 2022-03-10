/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:23:01 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/10 16:34:32 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*one_ret_null(char **s)
{
	free(*s);
	return (NULL);
}

char	**d_ret_null(char ***s)
{
	char	**tmp;

	tmp = *s;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(tmp);
	return (NULL);
}
