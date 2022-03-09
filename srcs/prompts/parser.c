/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:10:14 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/09 15:09:55 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_dlm(char prev, char *de, int word_in)
{
	if (!word_in)
	{
		if (!prev)
			*de = ' ';
		else
			*de = prev;
	}
	return (1);
}

static int	count_var(char *s)
{
	int		counts;
	int		word_in;
	char	delimiter;

	counts = 0;
	word_in = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '"' || *s == ' ')
		{
			if ((*s == delimiter) && word_in)
			{
				word_in = 0;
				counts++;
			}
		}
		else
			word_in = set_dlm(*(s - 1), &delimiter, word_in);
		s++;
	}
	if (word_in)
		counts++;
	return (counts);
}

static int	count_vbar(char *s)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == '|')
			cnt++;
		s++;
	}
	return (cnt);
}

void	parser(char *s)
{
	int		i;
	char	**res;
	char	**temp;
	char	delimiter;
	char	*b_p;

	temp = ft_split(s, '|');
	if (temp)
	{
		while (*temp)
		{
			
			temp++;
		} 
	}
	res = (char **)malloc((count_var(s) + 1) * sizeof(char *));
	if (res)
	{
		while (*s)
		{
			if (*s != '\'' && *s != '"' && *s != ' ')
			{
				b_p = s;
				if (!*(s - 1))
					delimiter = ' ';
				else
					delimiter = *(s - 1);
				while (*s && *s != delimiter)
					++s;
				res[i] = (char *)malloc(s - b_p + 1);
				if (!res[i])
				{
					free_double_pointer(res);
					break ;
				}
				ft_strlcpy(res[i++], b_p, (size_t)(s - b_p + 1));
			}
			else
				s++;
		}
	}
}
