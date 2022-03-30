/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:02:00 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/01 18:00:34 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(void)
{
	int	i;

	i = -1;
	while (g_state.envp[++i])
		ft_putendl_fd(g_state.envp[i], 1);
	g_state.exit_status = 0;
}
