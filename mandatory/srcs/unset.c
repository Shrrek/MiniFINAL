#include "../incs/minishell.h"

static int	ft_is_in_env(t_mini *minishell, char *var, size_t var_len)
{
	int	i;

	i = -1;
	while (minishell->mini_env[++i])
	{
		if (!ft_strncmp(minishell->mini_env[i], var, var_len)
			|| (!ft_strncmp(minishell->mini_env[i], var, var_len - 1)
				&& !minishell->mini_env[i][var_len - 1]))
			return (1);
	}
	return (0);
}

static char	**ft_unset_aux(t_mini *minishell, char *var, size_t var_len)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = -1;
	new_env = (char **)malloc(sizeof(char *)
			* ft_2dstrlen(minishell->mini_env));
	if (!new_env)
		return (NULL);
	while (minishell->mini_env[i])
	{
		if (!ft_strncmp(minishell->mini_env[i], var, var_len)
			|| !ft_strncmp(minishell->mini_env[i], var, var_len - 1))
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
	while (minishell->cmds[cmd][++i])
	{
		var = ft_join_chr(minishell->cmds[cmd][i], '=');
		var_len = ft_strlen(var);
		if (!ft_is_in_env(minishell, var, var_len))
		{
			free(var);
			return ;
		}
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
