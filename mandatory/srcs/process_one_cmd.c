#include "../incs/minishell.h"

static void	ft_exec_one_cmd(t_mini *minishell)
{
	pid_t	pid;
	char	*cmd_path;
	
	printf("El comando que le llega es:\n");
	ft_print2dstr(minishell->cmds[0]);
	signal(SIGINT, SIG_DFL);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		if (!minishell->cmds || !minishell->cmds[0] || !minishell->cmds[0][0] || !minishell->cmds[0][0][0])
			exit (EXIT_FAILURE);
		if (minishell->cmds[0][0][0] == '/')
		{
			execve(minishell->cmds[0][0], minishell->cmds[0],
				minishell->mini_env);
			exit(EXIT_FAILURE);
		}
		cmd_path = ft_get_command_path(minishell->cmds[0], minishell->mini_env);
		if (!cmd_path)
			exit(EXIT_FAILURE);
		execve(cmd_path, minishell->cmds[0], minishell->mini_env);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, ft_child_signal_handler);
		signal(SIGQUIT, ft_child_signal_handler);
		waitpid(pid, NULL, 0);
		signal(SIGINT, ft_signal_handler);
		signal(SIGQUIT, ft_signal_handler);
	}

}

/*static void	ft_history_exit(t_mini *minishell)
{
	if (ft_strcmp(minishell->cmds[0][0], "exit"))
		exit(EXIT_SUCCESS);
	if (ft_strcmp(minishell->cmds[0][0], "history"))
	{
		if (ft_strcmp(minishell->cmds[0][1], "-c"))
			printf("history\n");
	}
}*/

void	ft_process_one_cmd(t_mini *minishell)
{
	int	j;

	j = 0;
	ft_delete_quotes(minishell->cmds[0][0]);
	if (ft_strcmp(minishell->cmds[0][0], "exit"))
		exit(EXIT_SUCCESS);
	else if (ft_strcmp(minishell->cmds[0][0], "history"))
	{
		if (ft_strcmp(minishell->cmds[0][1], "-c"))
			printf("history\n");
	}
	else if (ft_search_redir(minishell->cmds[0]))
	{
		printf("reidr\n");
		ft_process_redir(minishell, 0);
	}
	else
	{
		while (minishell->cmds[0][++j])
			ft_delete_quotes(minishell->cmds[0][j]);
		if (ft_is_builtin(minishell, 0))
			ft_process_builtin(minishell, 0, 0);
		else
			ft_exec_one_cmd(minishell);
	}
}

/*
hasta ahora para identificar de que fd reciben las entradas los comandos identifica que tipoi de redireccion de entrada final tiene el comando y en funciuon de eso ejecutaba una y otra opcion
Ahora yo tengo que identificar con una funcion si la ultima redireccion es un here-doc o no.
	- esta funcion devuelve 0 si no habia una redireccion, 1 si la redireccion es normal y 2 si es un here doc
Si es un here_doc:
	- lo primero que tengo que hacer es 
*/