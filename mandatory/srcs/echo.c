/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:21:37 by jperales          #+#    #+#             */
/*   Updated: 2023/03/28 19:21:40 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	ft_write_args(char **cmd, int fd)
{
	int	i;
	int	len;

	i = 0;
	len = (int)ft_2dstrlen((const char **)cmd) - 1;
	while (cmd[++i])
	{
		if (i == len)
		{
			ft_putstr_fd(fd, cmd[i], 0);
			break ;
		}
		ft_putstr_fd(fd, cmd[i], 0);
		ft_putstr_fd(fd, " ", 0);
	}
}

static int	ft_check_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

/*
 * Procesa el comando echo. Redirige el programa dependiendo de si el usuario ha introducido
 * el argumento -n o no.
 */
void	ft_echo(t_mini *minishell, int cmd, int fd)
{
	if (ft_check_n(minishell->cmds[cmd][1]))
		ft_write_args(&minishell->cmds[cmd][1], fd);
	else
	{
		if (minishell->cmds[cmd][1] != NULL)
			ft_write_args(minishell->cmds[cmd], fd);
		ft_putstr_fd(fd, "\n", 0);
	}
}
