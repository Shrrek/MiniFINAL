#include "../incs/minishell.h"

/* CONTROLAR SI ALGUN FD ES NEFGATIVO NO SE PROCVESAN LOS COMANDOS */
static void	ft_exec_final_parent(t_mini *minishell, pid_t pid)
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

static void	ft_exec_final_child(t_mini *minishell, int *fd, int i)
{
	char	*cmd_path;

	minishell->or_outfd = dup(STDOUT_FILENO);
	if (fd)
		ft_check_fd(fd[0], STDIN_FILENO);
	if (minishell->here_doc)
		ft_process_here_doc(minishell);
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

static void	ft_exec_final_cmd(t_mini *minishell, int i, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		ft_exec_final_child(minishell, fd, i);
	else
		ft_exec_final_parent(minishell, pid);
}

void	ft_process_final_cmd(t_mini *minishell, int i)
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
		ft_exec_final_cmd(minishell, i, fd);
	else if (!fd)
	{
		ft_exec_final_cmd(minishell, i, fd);
		return ;
	}
	if (fd)
		free(fd);
}
