/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:01:03 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/26 13:15:36 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*new_env_lst(char **k_v)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->key = k_v[0];
	new->value = k_v[1];
	new->next = NULL;
	return (new);
}

static char	**set_k_v(char *s)
{
	char	**res;

	res = ft_split(s, '=');
	if (!res)
		exit(1);
	if (!ft_strchr(res[1], '\'') && !ft_strchr(res[1], '"'))
		ft_strlcpy(res[1], res[1], ft_strchr(res[1], ' ') - res[1]);
	else if (ft_strchr(res[1], '\''))
		ft_strlcpy(res[1], res[1] + 1, ft_strchr(res[1] + 1, '\'') - res[1]);
	else if (ft_strchr(res[1], '"'))
		ft_strlcpy(res[1], res[1] + 1, ft_strchr(res[1] + 1, '"') - res[1]);
	return (res);
}

void	ft_export(t_env *env, char *s)
{
	char	**k_v;

	while (*s == ' ')
		s++;
	while (env->next)
		env = env->next;
	k_v = set_k_v(s);
	env->next = new_env_lst(k_v);
	free(k_v);
}
