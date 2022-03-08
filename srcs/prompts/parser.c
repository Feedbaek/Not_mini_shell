/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:10:14 by sungmcho          #+#    #+#             */
/*   Updated: 2022/03/08 18:48:50 by sungmcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static int	set_fd(char *s, int token)
// {	
// 	int		j;
// 	char	*file;

// 	j = 0;
// 	while (s[j] != ' ')
// 		j++;
// 	file = (char *)malloc(j + 1);
// 	if (!file)
// 	{
// 		ft_putendl_fd("Errors on malloc function.\n", 2);
// 		return (-1);
// 	}
// 	ft_strlcpy(file, s, j + 1);
// 	ft_putendl_fd(file, 1);
// 	if (token == O_RDONLY)
// 		g_state.in_fd = open(file, token);
// 	else
// 		g_state.out_fd = open(file, token);
// 	if (g_state.in_fd < 0 || g_state.out_fd < 0)
// 	{
// 		ft_putendl_fd("Errors on opening a file.\n", 2);
// 		free(file);
// 		return (-1);
// 	}
// 	free(file);
// 	return (j);
// }



			
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

static void	ft_memfree(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


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

void	parser(char *s)
{
	int		i;
	char	**res;
	char	delimiter;
	char	*b_p;

	i = 0;
	res = (char **)malloc((count_var(s) + 1) * sizeof(char *));
	if (res)
	{
		while (*s)
		{
			if (*s != '\'' && *s != '"' && *s != ' ' && *s != '|')
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
					ft_memfree(res);
					break ;
				}
				ft_strlcpy(res[i++], b_p, (size_t)(s - b_p + 1));
			}
			else
				s++;
		}
	}
}
