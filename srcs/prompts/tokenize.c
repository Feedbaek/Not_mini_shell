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

static int	count_chunk(char *s)
{
	int		counts;
	int		word_in;
	char	delimiter;

	counts = 0;
	word_in = 0;
	delimiter = ' ';
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

static void	str_processer(char *s, char *b_p, char delimiter, t_parsed *cmds)
{
	char	*res;
	char	*temp;

	res = (char *)malloc(s - b_p + 1);
	if (!res)
		malloc_error();
	ft_strlcpy(res, b_p, (size_t)(s - b_p + 1));
	if (delimiter != '\'')
	{
		temp = process_env_var(res);
		free(res);
		res = temp;
	}
	cmds->de = delimiter;
	cmds->token = res;
}

static void	cmd_spliter(char *s, t_parsed *var)
{
	int		i;
	char	delimiter;
	char	*b_p;

	i = 0;
	delimiter = ' ';
	while (*s)
	{
		if (*s != '\'' && *s != '"' && *s != ' ')
		{
			b_p = s;
			if (i)
				delimiter = *(s - 1);
			while (*s && *s != delimiter)
				++s;
			str_processer(s, b_p, delimiter, &var[i]);
			i++;
			if (!*s)
				break ;
		}
		s++;
	}
	var[i].de = 0;
	var[i].token = NULL;
}

void	tokenize_line(char **split, t_parsed **parsed)
{
	int	i;

	i = 0;
	while (split[i])
	{
		parsed[i] = (t_parsed *)malloc((count_chunk(split[i]) + 1) \
					* sizeof(t_parsed));
		if (!parsed[i])
			malloc_error();
		cmd_spliter(split[i], parsed[i]);
		i++;
	}
}
