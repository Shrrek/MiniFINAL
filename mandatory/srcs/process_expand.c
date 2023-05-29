/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:26:51 by jperales          #+#    #+#             */
/*   Updated: 2023/03/28 19:26:54 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	*ft_get_env_var_val(char *var, char **env)
{
	size_t		var_len;
	size_t		env_var_len;
	char		*env_var_content;
	int			i;
	extern int	g_status;

	i = -1;
	var_len = ft_strlen(var);
	if (var[0] == '?')
		return (ft_itoa(g_status));
	while (env[++i])
	{
		env_var_len = ft_get_chrlen(env[i], '=');
		if (env_var_len == var_len)
		{
			if (!ft_strncmp(env[i], var, var_len))
			{
				env_var_content = ft_strdup(&env[i][env_var_len + 1]);
				return (env_var_content);
			}
		}
	}
	return (NULL);
}

static char	*ft_get_var(char *str)
{
	int		i;
	char	*var;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != ' ' && str[i] != 34 && str[i]
		!= 39 && str[i] != '$' && str[i] != '=')
		i++;
	var = (char *)malloc(sizeof(char) * i + 1);
	if (!var)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != 34 && str[i]
		!= '$' && str[i] != 39 && str[i] != '=' && str[i] != '+')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

static void	ft_treat_expand(char **cmd, int i, int *j, char **env)
{
	char	*var;
	char	*var_value;
	char	*tmp;

	var = ft_get_var(&cmd[i][*j + 1]);
	var_value = ft_get_env_var_val(var, env);
	tmp = cmd[i];
	if (!var_value)
		cmd[i] = ft_var_not_found(cmd[i], var);
	else
		cmd[i] = ft_expand(var, var_value, cmd[i]);
	while (cmd[i][*j] && cmd[i][*j] != 34 && cmd[i][*j] != '$' && cmd[i][*j]
		!= 32 && cmd[i][*j] != 39 && cmd[i][*j] != '=')
		(*j)++;
	free(var);
	free(var_value);
	free(tmp);
}

static void	ft_process_expand_aux(char **cmd, int i, int *j, char **env)
{
	if (cmd[i][*j] == 39)
		ft_pass_quotes(cmd[i], j);
	if (cmd[i][*j] == 34)
	{
		(*j)++;
		while (cmd[i][*j] && cmd[i][*j] != 34)
		{
			if (cmd[i][*j] == '$' && cmd[i][*j + 1] != ' ' &&
				cmd[i][*j + 1] != 34)
				ft_treat_expand(cmd, i, j, env);
			else
				(*j)++;
		}
	}
	if (cmd[i][*j] == '$' && cmd[i][*j + 1] != ' ')
		ft_treat_expand(cmd, i, j, env);
	else
		(*j)++;
}

void	ft_process_expand(char **cmd, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j])
			ft_process_expand_aux(cmd, i, &j, env);
	}
}
