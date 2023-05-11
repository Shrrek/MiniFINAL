#include "../incs/minishell.h"

static void	ft_check_fd(int fd1, int fd2)
{
	if (fd1 != 0)
	{
		dup2(fd1, fd2);
		close(fd1);
	}
}

static void	ft_exec_cmd_redir(char **cmds, int *fd, char **env, char *here_doc)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		return ;
	}
	if (pid == 0)
	{
		ft_check_fd(fd[0], STDIN_FILENO);
		ft_check_fd(fd[1], STDOUT_FILENO);
		if (here_doc != NULL)
			ft_process_here_doc(here_doc);
		cmd_path = ft_get_command_path(cmds, env);
		if (!cmd_path)
			return ;
		execve(cmd_path, cmds, env);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
}

static void	ft_process_redir_aux(t_mini *minishell,
	int i, char *input, char **cmds)
{
	int		infile;
	char	*here_doc;
	int		outfile;
	int		fd[2];
	char	*rest;

	here_doc = NULL;
	rest = ft_substr(input, i, ft_strlen(input) - i);
	if (ft_treat_fds(&infile, &outfile, rest, &here_doc) == -1)
		return ;
	fd[0] = infile;
	fd[1] = outfile;
	ft_exec_cmd_redir(cmds, fd, minishell->mini_env, here_doc);
}

static int	ft_get_cmds(char ***cmds, char *input)
{
	char	*cmd;
	int		i;

	i = 0;
	while (input[i] && input[i] != '<' && input[i] != '>')
		i++;
	cmd = ft_substr(input, 0, i);
	*cmds = ft_split(cmd, ' ');
	free(cmd);
	return (i);
}

/*
 * IMPORTANTE:
 * ME QUEDA AÑADIR UNA FUNCION QUE PERMITA SEGUIR O NO PROCESANDO LAS REDIRECCIONES EN FUNCION
 * DE COMO HA INTRODUCIDO EL SCRIPT EL USUARIO. SI INTRODUCE ALGUN ARGUMENTO DESPUES DE LAS REDIRECCIONES
 * LANZAMOS UN ERROR.
 */
void	ft_process_redir(t_mini *minishell, int cmd)
{
	char	*input;
	char	**cmds;
	int		i;

	input = ft_2dtostr(minishell->cmds[cmd]);
	i = ft_get_cmds(&cmds, input);
	ft_process_redir_aux(minishell, i, input, cmds);
	free(input);
	ft_free_2dstr(cmds);
}
