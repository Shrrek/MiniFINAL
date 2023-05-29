#include "../incs/minishell.h"

static void	ft_exec_multiple_parent(t_mini *minishell, pid_t pid, int *fd_pipe)
{
	int			status;
	extern int	g_status;

	signal(SIGINT, ft_child_signal_handler);
	signal(SIGQUIT, ft_child_signal_handler);
	waitpid(pid, &status, 0);
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
	if (minishell->here_doc)
	{
		free(minishell->here_doc);
		minishell->here_doc = NULL;
	}
	free(fd_pipe);
}

static void	ft_exec_multiple_child(t_mini *minishell,
	int *fd, int i, int *fd_pipe)
{
	char	*cmd_path;

	minishell->or_outfd = dup(STDOUT_FILENO);
	if (minishell->here_doc)
		ft_process_here_doc(minishell);
	close(fd_pipe[0]);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	if (fd)
		ft_check_fd(fd[0], STDIN_FILENO);
	if (fd)
		ft_check_fd(fd[1], STDOUT_FILENO);
	if (ft_is_builtin(minishell, i))
	{
		ft_process_builtin(minishell, i, STDOUT_FILENO);
		exit(0);
	}
	cmd_path = ft_get_command_path(minishell->cmds[i],
			minishell->mini_env, minishell);
	if (!cmd_path)
		exit(127);
	execve(cmd_path, minishell->cmds[i], minishell->mini_env);
	exit(127);
}

static void	ft_exec_multiple_cmds(t_mini *minishell, int i, int *fd)
{
	pid_t	pid;
	int		*fd_pipe;

	fd_pipe = (int *)ft_calloc(2, sizeof(int));
	if (!fd_pipe)
		return ;
	pipe(fd_pipe);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
		ft_exec_multiple_child(minishell, fd, i, fd_pipe);
	else
		ft_exec_multiple_parent(minishell, pid, fd_pipe);
}

void	ft_process_multiple_cmds(t_mini *minishell, int i)
{
	int	j;
	int	*fd;

	j = -1;
	fd = NULL;
	if (ft_search_redir(minishell->cmds[i]))
		fd = ft_process_redir(minishell, i);
	while (minishell->cmds[i][++j])
		ft_delete_quotes(minishell->cmds[i][j]);
	if (fd && fd[0] != -1 && fd[1] != -1)
		ft_exec_multiple_cmds(minishell, i, fd);
	else if (!fd)
	{
		ft_exec_multiple_cmds(minishell, i, fd);
		return ;
	}
	if (fd)
		free(fd);
}
