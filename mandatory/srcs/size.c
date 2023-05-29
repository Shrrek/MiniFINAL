#include "../incs/minishell.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

size_t	ft_2dstrlen(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

size_t	ft_3dstrlen(char ***str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_get_chrlen(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == c)
		i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
