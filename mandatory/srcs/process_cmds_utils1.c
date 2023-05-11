#include "../incs/minishell.h"

char	*ft_access_command(char **env_path, char *cmd)
{
	ssize_t	i;
	int		j;
	char	*dst;
	char	*dst2;

	i = -1;
	while (env_path[++i])
	{
		dst = ft_strjoin(ft_strjoin(env_path[i], "/"), cmd);
		j = access(dst, F_OK);
		if (j == 0)
		{
			dst2 = ft_strndup(dst, ft_strlen(dst));
			free(dst);
			return (dst2);
		}
		free(dst);
	}
	return (NULL);
}

int	ft_get_commands_path(t_mini *minishell)
{
	int		i;
	size_t	len;

	i = 0;
	while (ft_strncmp(minishell->mini_env[i],
			"PATH=", 5) && minishell->mini_env[i])
		i++;
	minishell->env_path = ft_split(minishell->mini_env[i], ':');
	minishell->env_path[0] = ft_substr(minishell->env_path[0],
			5, ft_strlen(minishell->env_path[0]) - 5);
	len = ft_3dstrlen(minishell->cmds);
	minishell->cmd_path = (char **)malloc(sizeof(char *) * (len + 1));
	if (!minishell->cmd_path)
		return (0);
	i = -1;
	while (++i < (int)len)
	{
		minishell->cmd_path[i]
			= ft_access_command(minishell->env_path, minishell->cmds[i][0]);
		if (!minishell->cmd_path[i])
		{
			printf("invalid command\n");
			return (0);
		}
	}
	minishell->cmd_path[i] = NULL;
	return (1);
}
