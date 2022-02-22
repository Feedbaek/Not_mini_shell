/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:53:09 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/22 16:24:26 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}
