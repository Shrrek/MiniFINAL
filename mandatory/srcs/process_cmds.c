#include "../incs/minishell.h"

typedef struct s_proc_cmd
{
	char	**cmds;
	int		redir;
	int		redir_type;
	int		fd[2];
}	t_proc_cmd;

void	ft_putstr_fd(int fd, char *str, int mode)
{
	char	*nl_str;

	if (str)
	{
		if (mode == 1)
		{
			nl_str = ft_strjoin(str, "\n");
			write(fd, nl_str, ft_strlen(nl_str));
			free(nl_str);
		}
		else
			write(fd, str, ft_strlen(str));
	}
}

/*
 * Printea un array 2d
 */
void	ft_print2dstr(char **str)
{
	// printf("\nPRINT\n");
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			printf("%s>\n", str[i]);
	}
}

void	ft_print3dstr(char ***str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
		{
			printf("cadena %d\n", i);
			ft_print2dstr(str[i]);
		}
	}
}

/*void	ft_get_cmd_attr(char **cmd, t_mini *minishell)//, t_proc_cmd *cmd_utils)
{
	char	*cmd_path;

	if (ft_search_redir(cmd))
	{
		printf("hay redireccion\n");
	}
	else
	{
		if (ft_is_builtin(minishell, 0))
			ft_process_builtin(minishell, 0, 0);
		else
		{
			pid_t	pid;
			pid = fork();
			if (pid == 0)
			{
				cmd_path = ft_get_command_path(minishell->cmds[0], minishell->mini_env);
				if (cmd_path)
					execve(cmd_path, cmd, minishell->mini_env);
				free(cmd_path);
				exit(1);
			}
			else
			{
				waitpid(pid, NULL, 0);
			}
		}
	}
}*/

void	ft_exec_final_cmd(t_mini *minishell, int i)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	printf("i = %d\n", i);
	ft_print2dstr(minishell->cmds[i]);
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		cmd_path = ft_get_command_path(minishell->cmds[i], minishell->mini_env);
		if (!cmd_path)
			return ;
		execve(cmd_path, minishell->cmds[i], minishell->mini_env);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_process_final_cmd(t_mini *minishell, int i)
{
	if (ft_search_redir(minishell->cmds[i]))
	{
		printf("redirecciones\n");
		return ;
	}
	else
	{
		if (ft_is_builtin(minishell, i))
			printf("builtin\n");
		else
			ft_exec_final_cmd(minishell, i);
	}
}

void	ft_process_final(t_mini *minishell, int i)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == 0)
	{
		cmd_path = ft_get_command_path(minishell->cmds[i], minishell->mini_env);
		if (!cmd_path)
			return ;
		execve(cmd_path, minishell->cmds[i], minishell->mini_env);
	}
	waitpid(pid, NULL, 0);
	dup2(minishell->or_infd, STDIN_FILENO);
}

void	ft_process_cmds(t_mini *minishell)
{
	int	len;
	int	i;

	i = 0;
	len = (int) ft_3dstrlen(minishell->cmds);
	if (len == 1)
		ft_process_one_cmd(minishell);
	else
	{
		while (minishell->cmds[++i] && minishell->cmds[i + 1] != NULL)
			ft_process_multiple_cmds(minishell, i);
		ft_process_final(minishell, i);
	}
}
