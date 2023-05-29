#include "../incs/minishell.h"

void	ft_process_here_doc(t_mini *minishell)
{
	int		fd[2];
	char	*line;
	char	*tmp;

	dup2(minishell->or_infd, STDIN_FILENO);
	pipe(fd);
	while (1)
	{
		line = readline(">");
		if (ft_strcmp(line, minishell->here_doc))
			break ;
		tmp = line;
		line = ft_join_chr(line, '\n');
		free(tmp);
		ft_putstr_fd(fd[1], line, 0);
		free(line);
	}
	free(line);
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
