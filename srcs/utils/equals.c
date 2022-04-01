#include <minishell.h>

int	equals(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2))
		if (!ft_strncmp(s1, s2, ft_strlen(s1)))
			return (1);
	return (0);
}
