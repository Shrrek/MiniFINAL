#include "../incs/minishell.h"

static int	ft_get_infile(char *str, int i)
{
	int		start;
	char	*file;
	int		is_open;

	while (str[++i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		start = i;
		while (str[i] && str[i] != ' ')
			i++;
		if (!str[i] || str[i] == ' ')
		{
			file = ft_substr(str, start, i - start);
			is_open = open(file, O_RDONLY);
			free(file);
			return (is_open);
		}
	}
	return (-1);
}

int	ft_set_infd(char *str)
{
	int		inredir;

	inredir = ft_get_redir(str, '<');
	if (inredir > -1)
		return (ft_get_infile(str, inredir));
	return (0);
}

int	ft_search_infd(char *input)
{
	int		inredir;

	inredir = ft_get_redir(input, '<');
	if (inredir > -1)
	{
		if (input[inredir + 1] == '<')
			return (2);
		return (1);
	}
	return (0);
}
