#include "../incs/minishell.h"

void	ft_exec_multiple_cmds(t_mini *minishell, int i)
{
	pid_t	pid;
	int		fd[2];
	char	*cmd_path;

	pipe(fd);
	pid = fork();
	//ft_print2dstr(minishell->cmds[i]);
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		if (ft_is_builtin(minishell, i))
		{
			ft_process_builtin(minishell, i, fd[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			cmd_path = ft_get_command_path(minishell->cmds[i],
					minishell->mini_env);
			if (!cmd_path)
				exit (EXIT_FAILURE);
			execve(cmd_path, minishell->cmds[i], minishell->mini_env);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	ft_process_multiple_cmds(t_mini *minishell, int i)
{
	int	j;

	j = -1;
	if (ft_search_redir(minishell->cmds[i]))
		ft_process_redir(minishell, i);
	else
	{
		while (minishell->cmds[i][++j])
			ft_delete_quotes(minishell->cmds[i][j]);
		ft_exec_multiple_cmds(minishell, i);		
	}

}
