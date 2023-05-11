#include "../incs/minishell.h"

void	ft_process_here_doc(char *delimiter)
{
	int		fd[2];
	char	*line;
	char	*tmp;

	pipe(fd);
	while (1)
	{
		line = readline("");
		if (ft_strcmp(line, delimiter))
			break ;
		tmp = line;
		line = ft_join_chr(line, '\n');
		free(tmp);
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

char	*ft_get_here_doc(char *str)
{
	int	start;
	int	i;

	i = ft_get_redir(str, '<');
	i++;
	while (str[++i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		start = i;
		while (str[i] && str[i] != ' ')
			i++;
		if (!str[i] || str[i] == ' ')
			return (ft_substr(str, start, i - start));
	}
	return (NULL);
}
