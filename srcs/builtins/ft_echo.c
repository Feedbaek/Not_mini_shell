/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:47:23 by sungmcho          #+#    #+#             */
/*   Updated: 2022/02/26 15:51:39 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_w_quote(char *s, long len)
{
	while (len)
	{
		write(1, s, 1);
		s++;
		len--;
	}
}

static void	print_wo_quote(char **comp, int n)
{
	if (!n)
		comp++;
	while (*comp)
	{
		if (*(comp + 1) != NULL)
		{
			ft_putstr_fd(*comp, 1);
			write(1, " ", 1);
		}
		else
			ft_putstr_fd(*comp, 1);
		comp++;
	}
}

void	ft_echo(char *s)
{
	char	*quote;
	char	*dquote;
	char	**comp;
	int		n;

	quote = ft_strchr(s, '\'');
	dquote = ft_strchr(s, '\"');
	comp = ft_split(s, ' ');
	if (!comp)
		exit(1);
	n = ft_strncmp(comp[0], "-n", 2);
	if (quote)
		print_w_quote(quote + 1, ft_strrchr(s, '\'') - quote - 1);
	else if (dquote)
		print_w_quote(dquote + 1, ft_strrchr(s, '\"') - dquote - 1);
	else
		print_wo_quote(comp, n);
	if (n)
		write(1, "\n", 1);
	while (*comp)
	{
		free(*comp);
		comp++;
	}
	free(comp);
}
