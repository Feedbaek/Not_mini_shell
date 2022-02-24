/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:25:35 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/23 14:37:25 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	del_env_lst(t_env *env, t_env *prev)
{
	prev->next = env->next;
	free(env->key);
	free(env->value);
	free(env);
}

void	ft_unset(t_env *env, char *s)
{
	t_env	*prev;
	t_env	*start;

	start = env;
	while (*s == ' ')
		s++;
	while (env)
	{
		prev = env;
		if (!ft_strncmp(env->key, s, ft_strlen(env->key)))
		{
			del_env_lst(env, prev);
			break ;
		}
		env = env->next;
	}
	env = start;
}
