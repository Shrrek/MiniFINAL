#include "../incs/minishell.h"

static int	*ft_process_redir_aux(t_mini *minishell,
	int i, char *input)
{
	int		infile;
	int		outfile;
	int		*fd;
	char	*rest;

	minishell->here_doc = NULL;
	rest = ft_substr(input, i, ft_strlen(input) - i);
	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
		return (NULL);
	ft_treat_fds(&infile, &outfile, rest, &minishell->here_doc);
	fd[0] = infile;
	fd[1] = outfile;
	return (fd);
}

static int	ft_get_cmds(char ***cmds, char *input)
{
	char	*cmd;
	int		i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
			ft_pass_quotes(input, &i);
		if (input[i] == '<' || input[i] == '>')
			break ;
	}
	cmd = ft_substr(input, 0, i);
	*cmds = ft_split(cmd, ' ');
	free(cmd);
	return (i);
}

int	*ft_process_redir(t_mini *minishell, int cmd)
{
	char	**cmds;
	char	**tmp;
	char	*input;
	int		*fd;
	int		i;

	input = ft_2dtostr(minishell->cmds[cmd]);
	i = ft_get_cmds(&cmds, input);
	tmp = minishell->cmds[cmd];
	minishell->cmds[cmd] = ft_2dstrdup((const char **)cmds);
	ft_free_2dstr(tmp);
	fd = ft_process_redir_aux(minishell, i, input);
	free(input);
	ft_free_2dstr(cmds);
	if (!fd)
		return (NULL);
	return (fd);
}
