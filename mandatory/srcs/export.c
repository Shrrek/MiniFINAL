/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:33:58 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:34:01 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Devuelve el indice de la cadena mas pequeña dentro de un array

static void	ft_print2dstr_export(char **str)
{
	int	i;
	int	j;
	int	*pos_lst;

	i = -1;
	pos_lst = ft_get_2dstr_order((const char **)str);
	while (str[++i])
	{
		printf("declare -x ");
		j = -1;
		while (str[pos_lst[i]][++j])
		{
			if (str[pos_lst[i]][j] == '=')
			{
				printf("%c", str[pos_lst[i]][j]);
				j++;
				printf("\"%s\"", &str[pos_lst[i]][j]);
				break ;
			}
			printf("%c", str[pos_lst[i]][j]);
		}
		printf("\n");
	}
	free(pos_lst);
}

char	**ft_create_newenv(char **env, char *new_var)
{
	char	**new_env;
	size_t	env_len;
	int		i;

	i = -1;
	env_len = ft_2dstrlen((const char **)env) + 2;
	new_env = (char **)malloc(sizeof(char *) * env_len);
	if (!new_env)
		return (NULL);
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = ft_strdup(new_var);
	new_env[++i] = NULL;
	ft_free_2dstr(env);
	return (new_env);
}

int	ft_export_var(t_mini *minishell, int i, int j, int k)
{
	char	**env_var_split;
	char	**input_split;
	char	*tmp;

	input_split = ft_split(minishell->cmds[i][j], '=');
	env_var_split = ft_split(minishell->mini_env[k], '=');
	if (ft_strcmp(input_split[0], env_var_split[0]))
	{
		if (ft_strchr(minishell->cmds[i][j], '=') != -1)
		{
			tmp = minishell->mini_env[k];
			minishell->mini_env[k] = ft_strdup(minishell->cmds[i][j]);
			free(tmp);
		}
		ft_free_2dstr(env_var_split);
		ft_free_2dstr(input_split);
		return (1);
	}
	ft_free_2dstr(env_var_split);
	ft_free_2dstr(input_split);
	return (0);
}

void	ft_export(t_mini *minishell, int i)
{
	int	j;
	int	k;

	j = 0;
	if (ft_2dstrlen((const char **)minishell->cmds[i]) == 1)
		ft_print2dstr_export(minishell->mini_env);
	else
	{
		while (minishell->cmds[i][++j])
		{
			k = -1;
			while (minishell->mini_env[++k])
			{
				if (ft_export_var(minishell, i, j, k))
					break ;
			}
			if (minishell->mini_env[k] == NULL)
				minishell->mini_env = ft_create_newenv(minishell->mini_env,
						minishell->cmds[i][j]);
		}
	}
}
