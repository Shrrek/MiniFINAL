#include "../incs/minishell.h"

static int	ft_open(char *file, size_t mode)
{
	int	i;

	i = open(file, O_WRONLY | mode | O_CREAT, 0660);
	free(file);
	return (i);
}

static int	ft_get_outfile(char *str, int i, int mode)
{
	int		start;
	char	*file;

	if (mode == 1)
		i++;
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
			if (mode == 1)
				return (ft_open(file, O_APPEND));
			return (ft_open(file, O_TRUNC));
		}
	}
	return (-1);
}

int	ft_set_outfd(char *str)
{
	int		outredir;
	char	redir_type;

	outredir = ft_get_redir(str, '>');
	if (outredir > -1)
	{
		if (str[outredir + 1] == '>')
			redir_type = 'a';
		else
			redir_type = 't';
		if (redir_type == 'a')
			return (ft_get_outfile(str, outredir, 1));
		return (ft_get_outfile(str, outredir, 0));
	}
	return (0);
}
