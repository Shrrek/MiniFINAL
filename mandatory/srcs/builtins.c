/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:15:11 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:15:15 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
* Redirige el programa el funcion del tipo del builtin introducido.
 * 	- Como hay algunos builtins cuyo funcion es mostrar informacion en la pantalla,
 * 	  esta funcion ha de recibir el fd correspondiente a la salida especificada por el usuario.
 * 
 */
void	ft_process_builtin(t_mini *minishell, int i, int outfd)
{
	if (ft_strcmp(minishell->cmds[i][0], "env"))
	{
		if (minishell->cmds[i][1] == NULL)
			ft_env(minishell->mini_env, outfd);
		else
			ft_putstr_fd(0, "Error. No arguments for env command.\n", 0);
	}
	else if (ft_strcmp(minishell->cmds[i][0], "echo"))
		ft_echo(minishell, i, outfd);
	else if (ft_strcmp(minishell->cmds[i][0], "pwd"))
		ft_putstr_fd(outfd, getcwd(minishell->curr_path, PATH_MAX), 1);
	else if (ft_strcmp(minishell->cmds[i][0], "cd"))
		ft_cd(minishell, i);
	else if (ft_strcmp(minishell->cmds[i][0], "unset"))
		ft_unset(minishell, i);
	else if (ft_strcmp(minishell->cmds[i][0], "export"))
		ft_export(minishell, i);
}

/*
 * Comprueba si un comando es un builtin o no
 */
bool	ft_is_builtin(t_mini *minishell, int i)
{
	if (ft_strcmp(minishell->cmds[i][0], "env") ||
		ft_strcmp(minishell->cmds[i][0], "echo") ||
		ft_strcmp(minishell->cmds[i][0], "pwd") ||
		ft_strcmp(minishell->cmds[i][0], "cd") ||
		ft_strcmp(minishell->cmds[i][0], "unset") ||
		ft_strcmp(minishell->cmds[i][0], "export"))
		return (true);
	return (false);
}
