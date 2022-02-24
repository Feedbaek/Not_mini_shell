/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:02:00 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/23 11:42:37 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putchar_fd('=', 1);
		if (env->value)
			ft_putendl_fd(env->value, 1);
		else
			ft_putchar_fd('\n', 1);
		env = env->next;
	}
	env = temp;
}
