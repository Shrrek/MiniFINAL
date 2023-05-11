#include "../incs/minishell.h"

/*
 * Funciones que comprueban si un comando es ejecutable o no.
 */

/*
 * Comprueba si existe un binario dentro del sistema correspondiente al comando pasado como parametro
 * 	- Añade el simbolo de directorio al directorio donde debemos buscar el comando
 * 	- Despues añade el comando
 * 	- Comprueba con la funcion acces() existe algun fichero o directorio que corresponda con el comando
 * 	- Repite este proceso hasta que encuentre una que corresponda o hasta que no haya mas directorios que comprobar
 * 	- Si ha encontrado un fichero o directorio que coincide, devuelve el mismo
 * 	- Si no, devuelve NULL
 */
static char	*ft_access_command(char **env_path, char *cmd)
{
	ssize_t	i;
	int		j;
	char	*dst;
	char	*dst2;

	i = -1;
	while (env_path[++i])
	{
		dst2 = ft_strjoin(env_path[i], "/");
		dst = ft_strjoin(dst2, cmd);
		free(dst2);
		j = access(dst, F_OK);
		if (j == 0)
			return (dst);
		free(dst);
	}
	return (NULL);
}

/*
 * Comprueba si un comando es ejecutable o no viendo si existe en el sistema.
 * 	- Encontrar la variable de entorno PATH
 * 	- Sustraer los directorios de los binarios.
 * 		+ Como la primera cadena aun contiene el nombre de la variable, lo subtraemos
 *	- Para ver si el comando existe en uno de los binarios del sistema se llama a la funcion ft_access_command()
 *		+ Si no se puede acceder al comando muestra el mensaje de error, libera la memoria y devuelve NULL.
 *		+ Si se puede acceder a él, devuelve el directorio donde se encuentra el comando dentro del sistema.
 */
char	*ft_get_command_path(char **cmd, char **env)
{
	char	*cmd_path;
	char	**env_path;
	char	*tmp;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) && env[i])
		i++;
	env_path = ft_split(env[i], ':');
	tmp = ft_substr(env_path[0], 5, ft_strlen(env_path[0]) - 5);
	free(env_path[0]);
	env_path[0] = ft_strdup(tmp);
	free(tmp);
	cmd_path = ft_access_command(env_path, cmd[0]);
	if (!cmd_path)
	{
		printf("invalid command\n");
		ft_free_2dstr(env_path);
		return (NULL);
	}
	ft_free_2dstr(env_path);
	return (cmd_path);
}
