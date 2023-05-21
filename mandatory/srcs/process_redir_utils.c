#include "../incs/minishell.h"

bool	ft_search_redir(char **cmd)
{
	int	i;
	int	j;

	i = -1;
	if (!cmd)
		return (false);
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (cmd[i][j] == 34 || cmd[i][j] == 39)
				ft_pass_quotes(cmd[i], &j);
			if (cmd[i][j] == '<' || cmd[i][j] == '>')
				return (true);
		}
	}
	return (false);
}

int	ft_get_redir(char *str, char redir)
{
	int	i;
	int	redir_index;

	i = -1;
	redir_index = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			ft_pass_quotes(str, &i);
		if (str[i] == redir)
		{
			if (str[i + 1] == redir)
			{
				redir_index = i;
				i++;
			}
			else
				redir_index = i;
		}
	}
	return (redir_index);
}
