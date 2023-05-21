/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:23:30 by jperales          #+#    #+#             */
/*   Updated: 2023/03/28 19:23:32 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_env(char **env, int outfd)
{
	int	i;
	int	index;

	i = -1;
	while (env[++i])
	{
		if (ft_strcmp(env[i], "="))
			continue ;
		index = ft_strchr(env[i], '=');
		if (index == 0)
			continue ;
		if (index != -1)
		{
			if (env[i][index - 1] != ' ')
				ft_putstr_fd(outfd, env[i], 1);
		}
	}
}
