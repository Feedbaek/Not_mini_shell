/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:53:09 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/26 13:37:56 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, BUFSIZ);
	if (!pwd)
		exit(1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}
