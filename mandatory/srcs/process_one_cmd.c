#include "../incs/minishell.h"

static void	ft_exec_one_cmd(t_mini *minishell, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		ft_exec_one_child(minishell, fd);
	else
		ft_exec_one_parent(minishell, pid);
}

static int	ft_process_one_bultin(t_mini *minishell, int *fd)
{
	int	exit_status;

	if (fd && fd[1] != 0)
	{
		exit_status = ft_process_builtin(minishell, 0, fd[1]);
		if (fd)
			free(fd);
		return (exit_status);
	}
	exit_status = ft_process_builtin(minishell, 0, 0);
	if (fd)
		free(fd);
	return (exit_status);
}

static	int	ft_process_one_cmd_aux(t_mini *minishell, int *fd)
{
	if (ft_is_builtin(minishell, 0))
		return (ft_process_one_bultin(minishell, fd));
	ft_exec_one_cmd(minishell, fd);
	return (0);
}

int	ft_process_one_cmd(t_mini *minishell)
{
	int	j;
	int	*fd;

	j = -1;
	fd = NULL;
	if (ft_search_redir(minishell->cmds[0]))
		fd = ft_process_redir(minishell, 0);
	while (minishell->cmds[0][++j])
		ft_delete_quotes(minishell->cmds[0][j]);
	if (fd && fd[0] != -1 && fd[1] != -1)
	{
		if (ft_is_builtin(minishell, 0))
			return (ft_process_one_bultin(minishell, fd));
		ft_exec_one_cmd(minishell, fd);
		if (fd)
			free(fd);
		return (0);
	}
	if (!fd)
		return (ft_process_one_cmd_aux(minishell, fd));
	if (fd)
		free(fd);
	return (0);
}
