#include "../incs/minishell.h"

static int	ft_treat_cmds(t_mini *minishell)
{
	int	i;
	int	len;

	i = -1;
	len = (int) ft_3dstrlen(minishell->cmds);
	if (len == 1)
		return (ft_process_one_cmd(minishell));
	else
	{
		while (minishell->cmds[++i] && minishell->cmds[i + 1] != NULL)
			ft_process_multiple_cmds(minishell, i);
		ft_process_final_cmd(minishell, i);
		return (0);
	}
}

static int	ft_parse_input(t_mini *minishell)
{
	extern int	g_status;

	if (!*minishell->input)
	{
		g_status = 0;
		return (0);
	}
	if (!ft_quote_pairs(minishell->input)
		|| !ft_parse_pipes(minishell->input) || !ft_parse_redir(minishell))
	{
		g_status = 2;
		return (0);
	}
	return (1);
}

static	int	ft_process_input_aux(t_mini *minishell)
{
	ft_free_3dstr(minishell->cmds);
	minishell->cmds = NULL;
	return (0);
}

int	ft_process_input(t_mini *minishell)
{
	int			i;
	int			j;

	if (ft_parse_input(minishell) == 0)
		return (0);
	i = -1;
	j = -1;
	minishell->input_pipes = ft_split_pipes(minishell->input);
	minishell->cmds = (char ***)malloc(sizeof(char **)
			* (ft_2dstrlen(minishell->input_pipes) + 1));
	if (!minishell->cmds)
		return (1);
	while (minishell->input_pipes[++i])
		minishell->cmds[++j] = ft_split_input(minishell->input_pipes[i], ' ');
	minishell->cmds[++j] = NULL;
	ft_free_2dstr(minishell->input_pipes);
	if (minishell->cmds[0][0] == NULL)
		return (ft_process_input_aux(minishell));
	i = -1;
	while (minishell->cmds[++i])
		ft_process_expand(minishell->cmds[i], minishell->mini_env);
	return (ft_treat_cmds(minishell));
}
