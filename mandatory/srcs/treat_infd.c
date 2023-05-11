#include "../incs/minishell.h"

static int	ft_get_infile(char *str, int i)
{
	int		start;
	char	*file;

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
			return (open(file, O_RDONLY));
		}
	}
	return (-1);
}

int	ft_set_infd(char *str)
{
	int		inredir;
	char	redir_type;

	//busco si hay redirecciones de entrada. Si devuelve -1 es que no habia, por lo que el infd en STDIN
	inredir = ft_get_redir(str, '<');
	if (inredir > -1)
	{
		if (str[inredir + 1] == '<')
			redir_type = 'h';
		else
			redir_type = 'r';
		if (redir_type == 'h')
			return (-2);//identificador de heredoc. como el heredoc no genera un fd, hay que sustituir STDIN por el fd de lectura de un pipe.- Esto se hace dentro del hijo.
		return (ft_get_infile(str, inredir));
	}
	return (0);
}

int	ft_search_infd(char *str)
{
	int		inredir;

	inredir = ft_get_redir(str, '<');
	if (inredir > -1)
	{
		if (str[inredir + 1] == '<')
			return (2);
		return (1);
	}
	return (0);
}
