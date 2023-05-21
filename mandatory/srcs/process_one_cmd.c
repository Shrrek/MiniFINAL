#include "../incs/minishell.h"

static void	ft_exec_one_parent(t_mini *minishell, pid_t pid)
{
	int			status;
	extern int	g_status;

	signal(SIGINT, ft_child_signal_handler);
	signal(SIGQUIT, ft_child_signal_handler);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
	if (minishell->here_doc)
	{
		free(minishell->here_doc);
		minishell->here_doc = NULL;
	}
	dup2(minishell->or_infd, STDIN_FILENO);
}

static void	ft_exec_one_child(t_mini *minishell, int *fd)
{
	char	*cmd_path;

	minishell->or_outfd = dup(STDOUT_FILENO);
	if (minishell->here_doc)
		ft_process_here_doc(minishell);
	if (fd)
		ft_check_fd(fd[0], STDIN_FILENO);
	if (fd)
		ft_check_fd(fd[1], STDOUT_FILENO);
	if (minishell->cmds[0][0][0] == '/' || (minishell->cmds[0][0][0]
		== '.' && minishell->cmds[0][0][1] == '/'))
	{
		execve(minishell->cmds[0][0], minishell->cmds[0],
			minishell->mini_env);
		exit(EXIT_FAILURE);
	}
	cmd_path = ft_get_command_path(minishell->cmds[0],
			minishell->mini_env, minishell);
	if (!cmd_path)
		exit(127);
	execve(cmd_path, minishell->cmds[0], minishell->mini_env);
	exit(127);
}

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
	{
		if (ft_is_builtin(minishell, 0))
			return (ft_process_one_bultin(minishell, fd));
		ft_exec_one_cmd(minishell, fd);
		return (0);
	}
	if (fd)
		free(fd);
	return (0);
}
