/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:10:41 by jperales          #+#    #+#             */
/*   Updated: 2023/03/28 19:10:44 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_change_env(t_mini *minishell, char *str, char *var)
{
	int		i;
	char	*tmp;
	size_t	var_len;

	i = -1;
	var_len = ft_strchr(str, '=');
	while (minishell->mini_env[++i])
	{
		if (!ft_strncmp(minishell->mini_env[i], str, var_len + 1))
		{
			tmp = minishell->mini_env[i];
			minishell->mini_env[i] = ft_strjoin(str, var);
			free(tmp);
			break ;
		}
	}
}

/*
 * 
 */
void	ft_cd(t_mini *minishell, int cmd)
{
	if (ft_2dstrlen((const char **)minishell->cmds[cmd]) == 1)
	{
		chdir(minishell->mini_home);
		ft_change_env(minishell, "PWD=", minishell->mini_home);
	}
	else
	{
		if (chdir(minishell->cmds[cmd][1]) == -1)
			printf("No such file or directory\n");
		else
		{
			ft_change_env(minishell, "OLDPWD=", minishell->curr_path);
			minishell->curr_path = getcwd(minishell->curr_path, PATH_MAX);
			ft_change_env(minishell, "PWD=", minishell->curr_path);
		}
	}
}
