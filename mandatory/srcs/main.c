/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:43:32 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:43:35 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
/* 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 */

int	g_status;

static void	ft_init(t_mini *minishell, const char **env)
{
	minishell->exit_status = 0;
	minishell->mini_env = ft_2dstrdup(env);
	minishell->input_split = NULL;
	minishell->input = NULL;
	minishell->curr_path = NULL;
	minishell->curr_path = getcwd(minishell->curr_path, PATH_MAX);
	minishell->mini_home = getenv("HOME");
	minishell->input_pipes = NULL;
	minishell->cmds = NULL;
	minishell->cmd_path = NULL;
	minishell->env_path = NULL;
	minishell->or_infd = dup(STDIN_FILENO);
	minishell->here_doc = NULL;
	rl_catch_signals = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	minishell;
	int		exit;

	(void)argv;
	if (argc == 1)
	{
		ft_init(&minishell, (const char **)envp);
		signal(SIGINT, ft_signal_handler);
		signal(SIGQUIT, ft_signal_handler);
		while (1)
		{
			minishell.input = readline("MiniTabaqueros >$ ");
			if (!minishell.input)
			{
				printf("exit\n");
				break ;
			}
			add_history(minishell.input);
			exit = ft_process_input(&minishell);
			if (exit == 1)
				break ;
			free(minishell.input);
			if (minishell.cmds)
			{
				ft_free_3dstr(minishell.cmds);
				minishell.cmds = NULL;
			}
			if (minishell.here_doc)
			{
				free(minishell.here_doc);
				minishell.here_doc = NULL;
			}
		}
		ft_general_free(&minishell);
		return (g_status);
	}
	printf("Error. Invalid arguments.\n");
	return (0);
}
