#include "../incs/minishell.h"

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
		printf("-----\n");
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

/*void	ft_exec_final_cmd(t_mini *minishell, int i)
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
			exit(EXIT_FAILURE);
		execve(cmd_path, minishell->cmds[i], minishell->mini_env);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
}*/
void	ft_process_final(t_mini *minishell, int i)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == 0)
	{
		cmd_path = ft_get_command_path(minishell->cmds[i], minishell->mini_env);
		if (!cmd_path)
			exit(EXIT_FAILURE);
		execve(cmd_path, minishell->cmds[i], minishell->mini_env);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	dup2(minishell->or_infd, STDIN_FILENO);
}
void	ft_process_final_cmd(t_mini *minishell, int i)
{
	int	j;

	j = -1;
	if (ft_search_redir(minishell->cmds[i]))
		ft_process_redir(minishell, i);
	else
	{
		while (minishell->cmds[i][++j])
			ft_delete_quotes(minishell->cmds[i][j]);
		if (ft_is_builtin(minishell, i))
			ft_process_builtin(minishell, i, 0);
		else
			ft_process_final(minishell, i);
	}
}



void	ft_process_cmd(t_mini *minishell)
{
	int	i;
	int	len;
	//t_proc_cmd	cmd_utils;

	i = -1;
	len = (int) ft_3dstrlen(minishell->cmds);
	if (len == 1)
	{
		ft_process_one_cmd(minishell);
	}
	else
	{
		//printf("varios comandos %d\n", len);
		while (minishell->cmds[++i] && minishell->cmds[i + 1] != NULL)
			ft_process_multiple_cmds(minishell, i);
		ft_process_final_cmd(minishell, i);
		//ft_process_final_cmd(minishell, i);
		//ft_get_cmd_attr(minishell->cmds[i], minishell);//, &cmd_utils);
	}
	//printf("terminado de procesar los comandos\n");
}

/*
  - Funcion que procesa el input introducido por el usuario.
  - En primer lugar comprueba si hay algun error de comillas, de pipes, o de redirecciones
  para dejar de procesar el input, mostrar el error correspondiente y volver a pedir un
  input al usuario.
  - Si no hay ningun error, pasa a splitear el input en funcion de sus pipes y despues splitear
  su resultado por espacios para almacenar todos los comandos y sus correspondientes argumentos
  en un array de 3 dimensiones.
  - Ahora que tenemos mas o menos estructurado el input del usuario, analizamos los dos comandos
  que son independientes: el history y el exit.
  - Si no es ninguno de estos dos comandos, procedemos a expandir las variables que puedan hacerlo.
  - 

*/
void	ft_process_input(t_mini *minishell)
{
	int	i;
	int	j;

	// Comprueba todos los errores que invalidan el input directamente. Me faltan cosas del parse redir.
	if (!*minishell->input || !ft_quote_pairs(minishell->input)
		|| !ft_parse_pipes(minishell->input) || !ft_parse_redir(minishell))
		return ;
	i = -1;
	j = -1;
	// separamos el input del usuario por pipes
	minishell->input_pipes = ft_split_pipes(minishell->input);
	//ft_print2dstr(minishell->input_pipes);
	minishell->cmds = (char ***)malloc(sizeof(char **)
			* (ft_2dstrlen((const char **)minishell->input_pipes) + 1));
	if (!minishell->cmds)
		return ;
	// a cada argumento resultante de dividir por pipes el input, se le splitea por espacios para diferenciar cual es el comando y cuales los argumentos.
	while (minishell->input_pipes[++i])
		minishell->cmds[++j] = ft_split_input(minishell->input_pipes[i], ' ');
	minishell->cmds[++j] = NULL;
	if (minishell->cmds[0][0] == NULL)//si nos meten solo espacios sale por aqui
	{
		ft_free_2dstr(minishell->input_pipes);
		ft_free_3dstr(minishell->cmds);
		return ;
	}
	ft_free_2dstr(minishell->input_pipes);
	minishell->input_pipes = NULL;
	// APARTIR DE AQUI PUEDE CAMBIAR EL ORDEN. SEGUN COMO VAYA DESARROLLANDO LOS PIPES Y LAS REDIRECCIONES, SE EXPANDIRAN LAS VARIABLES Y SE ELIMINARAN LAS COMILLAS  EN UNA PARTE DEL CODIGO
	// O EN OTRA
	i = -1;
	while (minishell->cmds[++i])
		ft_process_expand(minishell->cmds[i], minishell->mini_env);
	i = -1;
	/*while (minishell->cmds[++i])
	{
		j = -1;
		while (minishell->cmds[i][++j])
			ft_delete_quotes(minishell->cmds[i][j]);
	}*/
	/*printf("Antes de empezar a procesar, los comandos son:\n");
	ft_print3dstr(minishell->cmds);
	printf("\n");*/
	ft_process_cmd(minishell);
	//ft_process_cmds(minishell);
	ft_free_3dstr(minishell->cmds);
	minishell->cmds = NULL;
}
