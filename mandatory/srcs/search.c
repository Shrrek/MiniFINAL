#include "../incs/minishell.h"

bool	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

bool	ft_str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (!str[i]);
}

int	ft_strchr(const char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}
