/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:00:37 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/09 13:05:35 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	set_fd(char *s, int token)
{	
	char	*file;

	if (token == O_RDONLY)
	{
		g_state.in_fd = open(file, token);
		if (g_state.in_fd < 0)
			ft_putendl_fd("Errors on opening a file.\n", 2);
	}
	else
	{
		g_state.out_fd = open(file, token);
		if (g_state.out_fd < 0)
			ft_putendl_fd("Errors on opening a file.\n", 2);
	}
}

	// 	if (s[i] == '<' && s[i + 1] != '<')
	// 	{
	// 		j = set_fd(s[++i], O_RDONLY);
	// 		if (j == -1)
	// 			break ;
	// 		i += j;
	// 		continue ;
	// 	}
	// 	if (s[i] == '>' && s[i + 1] != '>')
	// 	{
	// 		j = set_fd(s[++i], O_WRONLY);
	// 		if (j == -1)
	// 			break ;
	// 		i += j;
	// 		continue ;
	// 	}
	// 	if (s[i] == '>' && s[i + 1] == '>')
	// 	{
	// 		j = set_fd(s[i + 2], O_APPEND);
	// 		if (j == -1)
	// 			break ;
	// 		i = i + j + 2;
	// 		continue ;
	// 	}
	// }
