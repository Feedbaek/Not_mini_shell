/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:30:20 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/23 12:38:17 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*new_lst(char *s)
{
	t_env	*new;
	char	**k_v;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	k_v = ft_split(s, '=');
	new->key = k_v[0];
	new->value = k_v[1];
	new->next = NULL;
	free(k_v);
	return (new);
}

static void	add_last_lst(t_env *lst, char *s)
{
	while (lst->next)
		lst = lst->next;
	lst->next = new_lst(s);
}

t_env	*cpy_env(char **env)
{
	int		i;
	t_env	*temp;

	i = 0;
	while (env[i])
	{
		if (i == 0)
			temp = new_lst(env[i]);
		else
			add_last_lst(temp, env[i]);
		i++;
	}
	return (temp);
}
