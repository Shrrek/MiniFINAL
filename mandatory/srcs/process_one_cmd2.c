#include "../incs/minishell.h"

void	ft_exec_one_parent(t_mini *minishell, pid_t pid)
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

void	ft_exec_one_child(t_mini *minishell, int *fd)
{
	char	*cmd_path;

	minishell->or_outfd = dup(STDOUT_FILENO);
	if (minishell->here_doc)
	{
		printf("AQUI\n");
		signal(SIGINT, ft_heredoc_signal);
		signal(SIGQUIT, ft_signal_handler);
		ft_process_here_doc(minishell);
		//signal(SIGINT, SIG_DFL);
		//signal(SIGQUIT, SIG_DFL);
	}
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
