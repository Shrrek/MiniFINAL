#include "../incs/minishell.h"

static char	**ft_unset_aux(t_mini *minishell, char *var, size_t var_len)
{
	char	**new_env;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = -1;
	len = ft_2dstrlen((const char **)minishell->mini_env);
	new_env = (char **)malloc(sizeof(char *) * len);
	if (!new_env)
		return (NULL);
	while (i < len)
	{
		if (!ft_strncmp(minishell->mini_env[i], var, var_len)
			|| (!ft_strncmp(minishell->mini_env[i], var, var_len - 1)
				&& !minishell->mini_env[i][var_len - 1]))
		{
			while (minishell->mini_env[i])
			{
				new_env[++j] = ft_strdup(minishell->mini_env[i + 1]);
				i++;
			}
			return (new_env);
		}
		else
			new_env[++j] = ft_strdup(minishell->mini_env[i]);
		i++;
	}
	new_env[++j] = NULL; // lo sabia
	ft_free_2dstr(new_env);
	return (NULL);
}

void	ft_unset(t_mini *minishell, int cmd)
{
	size_t	var_len;
	char	*var;
	char	**new_env;
	char	**tmp;
	int		i;

	i = 0;
	/*if (minishell->cmds[cmd][1] == NULL)
		return ;*/
	while (minishell->cmds[cmd][++i])
	{
		var = ft_join_chr(minishell->cmds[cmd][i], '=');
		var_len = ft_strlen(var);
		new_env = ft_unset_aux(minishell, var, var_len);
		if (!new_env)
		{
			free(var);
			continue ;
		}
		tmp = minishell->mini_env;
		minishell->mini_env = ft_2dstrdup((const char **)new_env);
		ft_free_2dstr(tmp);
		ft_free_2dstr(new_env);
		free(var);
	}
}
