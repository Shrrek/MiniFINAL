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

/*
 * Muestra todas las variables del sistema con valor. Como su salida se puede redireccionar,
 * recibe el fd de salida especificado por el usuario.
 */
void	ft_env(char **env, int outfd)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strchr(env[i], '=') != -1)
			ft_putstr_fd(outfd, env[i], 1);
	}
}
