/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-p <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:10:01 by sperez-p          #+#    #+#             */
/*   Updated: 2023/05/23 18:10:04 by sperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	ft_numeric_error(t_mini *minishell, int i)
{
	extern int	g_status;

	ft_putstr_fd(0, "exit\n", 0);
	ft_putstr_fd(0, "Minitabaqueros: exit: ", 0);
	ft_putstr_fd(0, minishell->cmds[i][1], 0);
	ft_putstr_fd(0, ": numeric argument required\n", 0);
	g_status = 255;
	return (1);
}

static int	ft_exit_multiple_args(t_mini *minishell, int i)
{
	extern int	g_status;

	if (ft_str_is_digit(minishell->cmds[i][1]))
	{
		ft_putstr_fd(0, "exit\n", 0);
		ft_putstr_fd(0, "Minitabaqueros: exit: too many arguments\n", 0);
		g_status = 0;
		return (0);
	}
	else
		return (ft_numeric_error(minishell, i));
}

int	ft_exit(t_mini *minishell, int i)
{
	int			len;
	extern int	g_status;

	len = ft_2dstrlen(minishell->cmds[i]);
	if (len == 1)
	{
		ft_putstr_fd(0, "exit\n", 0);
		g_status = 0;
	}
	else if (len == 2)
	{
		if (ft_str_is_digit(minishell->cmds[i][1]))
		{
			g_status = ft_atoi(minishell->cmds[i][1]);
			ft_putstr_fd(0, "exit\n", 0);
			return (1);
		}
		else
			return (ft_numeric_error(minishell, i));
	}
	else
		return (ft_exit_multiple_args(minishell, i));
	return (1);
}
