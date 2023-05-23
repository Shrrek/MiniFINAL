/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-p <sperez-p@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:15:11 by sperez-p          #+#    #+#             */
/*   Updated: 2023/05/11 11:15:15 by sperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	ft_process_builtin_aux(t_mini *minishell, int i)
{
	extern int	g_status;

	if (ft_strcmp(minishell->cmds[i][0], "exit"))
		return (ft_exit(minishell, i));
	else if (ft_strcmp(minishell->cmds[i][0], "history"))
	{
		if (minishell->cmds[i][1])
		{
			ft_delete_quotes(minishell->cmds[i][1]);
			if (ft_strcmp(minishell->cmds[i][1], "-c"))
				rl_clear_history();
		}
	}
	else if (ft_str_is_digit(minishell->cmds[i][0]))
	{
		ft_putstr_fd(STDOUT_FILENO, "MiniTabaqueros: ", 0);
		ft_putstr_fd(STDOUT_FILENO, minishell->cmds[i][0], 0);
		ft_putstr_fd(STDOUT_FILENO, ": command not found\n", 0);
		g_status = 127;
	}
	return (0);
}

static int	ft_process_builtin_aux_two(t_mini *minishell, int i, int outfd)
{
	extern int	g_status;

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
	g_status = 0;
	return (0);
}

int	ft_process_builtin(t_mini *minishell, int i, int outfd)
{
	extern int	g_status;

	if (ft_strcmp(minishell->cmds[i][0], "history") ||
		ft_strcmp(minishell->cmds[i][0], "exit") ||
		ft_str_is_digit(minishell->cmds[i][0]))
		return (ft_process_builtin_aux(minishell, i));
	else
		return (ft_process_builtin_aux_two(minishell, i, outfd));
	return (0);
}

bool	ft_is_builtin(t_mini *minishell, int i)
{
	if (ft_strcmp(minishell->cmds[i][0], "env") ||
		ft_strcmp(minishell->cmds[i][0], "echo") ||
		ft_strcmp(minishell->cmds[i][0], "pwd") ||
		ft_strcmp(minishell->cmds[i][0], "cd") ||
		ft_strcmp(minishell->cmds[i][0], "unset") ||
		ft_strcmp(minishell->cmds[i][0], "export") ||
		ft_strcmp(minishell->cmds[i][0], "exit") ||
		ft_strcmp(minishell->cmds[0][0], "history") ||
		ft_str_is_digit(minishell->cmds[i][0]))
		return (true);
	return (false);
}
