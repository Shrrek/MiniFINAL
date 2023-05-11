#include "../incs/minishell.h"

int	ft_is_builtin(t_mini *minishell, int i)
{
	//ft_print2dstr(minishell->mini_env);
	if (ft_strcmp(minishell->cmds[i][0], "env"))
	{
		if (minishell->cmds[i][1] == NULL)
			ft_print2dstr(minishell->mini_env);
		else
			printf("Env error. No puede ir con argumentos\n");
	}
	else if (ft_strcmp(minishell->cmds[i][0], "echo"))
		printf("Entrando en echo\n");
	else if (ft_strcmp(minishell->cmds[i][0], "pwd"))
		printf("Entrando en pwd\n");
	else if (ft_strcmp(minishell->cmds[i][0], "cd"))
		printf("Entrando en cd\n");
	else if (ft_strcmp(minishell->cmds[i][0], "unset"))
		ft_unset(minishell, i);
	else if (ft_strcmp(minishell->cmds[i][0], "export"))
		printf("Entrando en export\n");
	else
		return (0);
	//ft_print2dstr(minishell->mini_env);
	return (1);
	/*
	else if (ft_str_equals(minishell->next_line_split[0], "echo"))
		ft_echo(minishell->next_line_split);
	else if (ft_str_equals(minishell->next_line_split[0], "pwd"))
		printf("%s\n", getcwd(minishell->mini_path, 1000));
	else if (ft_str_equals(minishell->next_line_split[0], "cd"))
		ft_cd(minishell);
	else if (ft_str_equals(minishell->next_line_split[0], "unset"))
		ft_unset(minishell);
	else if (ft_str_equals(minishell->next_line_split[0], "export"))
		ft_export(minishell)*/
}


void	ft_process_one_cmd(t_mini *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("");
		return ;
	}
	if (pid == 0)
		execve(minishell->cmd_path[0], minishell->cmds[0], minishell->mini_env);
	else
		waitpid(pid, NULL, 0);
}



int ft_2dcontlen(char **str)
{
	int len;
	int i;
	int j;
	int count;

	i = -1;
	if (!str)
		return (0);
	len = ft_2dstrlen((const char **)str);
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			count++;
		if (i != len)
			count++;
	}
	return (count);
}

char *ft_2dtostr(char **str)
{
	char *dst;
	int i;
	int j;
	int k;
	int len;

	len = ft_2dstrlen((const char **)str);
	if (!str)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * ft_2dcontlen(str) + 1);
	if (!dst)
		return (NULL);
	i = -1;
	k = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			dst[++k] = str[i][j];
		if (i != len)
			dst[++k] = ' ';
	}
	dst[++k] = '\0';
	return (dst);
}

int	ft_search_redir(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '<' || input[i] == '>')
			return (i);
	}
	return (0);

}

void	ft_get_redir(t_mini *minishell, char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				i++;
				minishell->parse_cmd=outredirappend = i + 1;
			}
			else
				minishell->parse_cmd->outredirtrunc = i + 1;
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				i++;
				minishell->parse_cmd->here_doc = i + 1;
			}
			minishell->parse_cmd->inredir = i + 1;
		}
		i++;
	}
}

void	ft_treat_redir(t_mini *minishell, char *input)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = -1;
	outfile_fd = -1;
	if (minishell->parse_cmd->inredir > 0 || minishell->parse_cmd->here_doc > 0)
	{
		if (minishell->parse_cmd->inredir > minishell->parse_cmd->here_doc)
			infile_fd = minishell->parse_cmd->inredir;
		else
			infile_fd = minishell->parse_cmd->here_doc;
	}
	if (minishell->parse_cmd->outredirtrunc > 0 || minishell->parse_cmd->outredirappend > 0)
	{
		if (minishell->parse_cmd->outredirtrunc > minishell->parse_cmd->outredirappend)
			outfile_fd = minishell->parse_cmd->outredirtrunc;
		else
			outfile_fd = minishell->parse_cmd->outredirappend
	}
	int i;
	int j;

	i = 0;
	j = 0;
	char	*infile;
	if (infile_fd > 0)
	{
		while (input[i] == ' ' && input[i])
		{
			i++;
			infile_fd = i;
		}
		while (input[i] != ' ' && input[i])
		{
			i++;
			j++;
		}
		infile = ft_substr((const char *)input, inredir, j);
		infile_fd = open(infile, O_RDONLY); 
	}
	if (outfile_fd > 0)
	{
		while (input[i] == ' ' && input[i])
		{
			i++;
			infile_fd = i;
		}
		while (input[i] != ' ' && input[i])
		{
			i++;
			j++;
		}
		infile = ft_substr((const char *)input, inredir, j);
		infile_fd = open(infile, O_RDONLY);
	}
	if (inredir > 0)
	{
		while (input[i] == ' ' && input[i])
		{
			i++;
			inredir = i;
		}
		printf("input desde despues de la redireccion: %s\n", &input[inredir]);
		while (input[i] != ' ' && input[i])
		{
			i++;
			j++;
		}
		printf("input despues del archvo = %s\n", &input[i]);
		inredir_file = ft_substr((const char *)input, inredir, j);
		printf("inredir file = %s\n", inredir_file);
		int infile = open(inredir_file, O_RDONLY);
		if (infile == -1)
			printf("error al abrir el archivo");
	}
}

void	ft_funcion_principal(char **cmd, t_mini *minishell)
{
	int len;
	char	*input;

	len = (int)ft_3dstrlen(minishell->cmds);
	printf("Cantidad de comandos: %d\n", len);
	if (len == 1)
	{
		if (ft_is_builtin(minishell, 0))
			printf("es builtin\n");
		else
		{
			/*if (!ft_get_commands_path(minishell))
				return;
			printf("\n\nCOMMANDS PATH\n");
			ft_print2dstr(minishell->cmd_path);
			printf("\n\n");*/
			// todo lo del comando unificado en una sola linea
			input = ft_2dtostr(cmd);
			printf("input = %s\n", input);
			char	*redir_split = ft_split(input, '')
			if (ft_search_redir(input))
			{
				int i = -1;
				int	inredir = -1;
				int	outredir = -1;
				int	outredir1 = -1;
				int	here_doc = -1;
				//identificamos el tipo de redireccion y devolvemos su posicion
				while (input[i])
				{
					if (input[i] == '>')
					{
						if (input[i + 1] == '>')
						{
							i++;
							outredir1 = i + 1;
						}
						else
							outredir = i + 1;
					}
					else if (input[i] == '<')
					{
						if (input[i + 1] == '<')
						{
							i++;
							here_doc = i + 1;
						}
						inredir = i + 1;
					}
					i++;
				}
				i = inredir;
				int j= 0;
				char	*inredir_file;
				if (inredir > 0)
				{
					while (input[i] == ' ' && input[i])
					{
						i++;
						inredir = i;
					}
					printf("input desde despues de la redireccion: %s\n", &input[inredir]);
					while (input[i] != ' ' && input[i])
					{
						i++;
						j++;
					}
					printf("input despues del archvo = %s\n", &input[i]);
					inredir_file = ft_substr((const char *)input, inredir, j);
					printf("inredir file = %s\n", inredir_file);					
					int infile = open(inredir_file, O_RDONLY);
					if (infile == -1)
						printf("error al abrir el archivo");
				}
				else if (outredir1 > 0)
					printf("outredir1\n");
				else if (outredir > 0)
					printf("outredir\n");
				else if (here_doc > 0)
					printf("here_doc\n");

					//si encuentra la redireccion de entrada o de salida
						//si la siguiente posicion tambien es una redireccion
							//posicion << o >>
						//guardo posicion < o >
				//si hay redirecciones de salida
					//si es mayor >
						//substrae el nombre del archivo
						//devuelve si fd
					//si es mayor >>
						//substrae el nombre del archivo
						//devuelve si fd
				// si hay redirecciones de entrada
					//sustrae el nombre del archivo
					//devuelve su fd
				//si ha habido redireccion de entrada
					//dupeamos el contenido de ese fd al STDIN_FILENO
					//closeamos ese fd
				//si hay redireccion de salida
					//creamos el fork
					//guardamos el fd del outfilefd
					//duplicamos el fd del artchivo en el infile fd
					//ejecutamos el comando

			}
			//ft_process_one_cmd(minishell);
		}
	}
}
/*
echo pepe < a cat << l
*/

/*
Recibo minishell->cmds[i]
hay que inicializar un fd de entrada y uno de salida.
la unifico en una variable que separa su contenido por redirecciones
recorro la cadena en busca de redirecciones de salida y me quedo con el ultimo 
*/

/*SI LA REDIRECCION VA ENTRECOMILLADA NO SE TRATA*/

struct typedef s_cmd
{
	int	inredir;
	int	outredirtrunc;
	int	outredirappend;
	int	here_doc;

	char	**args;
}	t_cmd;

void	ft_reset_input(t_mini *minishell)
{
	minishell->parse_cmd->inredir = -1;
	minishell->parse_cmd->outredirtrunc = -1;
	minishell->parse_cmd->outredirappend = -1;
	minishell->parse_cmd->here_doc = -1;
	ft_free_2dstr(minishell->parse_cmd->args);
	minishell->parse_cmd->args = NULL;
}
