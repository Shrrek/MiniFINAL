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

static void	ft_init(t_mini *minishell, const char **env)
{
	minishell->mini_env = ft_2dstrdup(env);
	minishell->input_split = NULL;
	minishell->input = NULL;
	minishell->curr_path = NULL;
	minishell->curr_path = getcwd(minishell->curr_path, PATH_MAX); // esto si almacena en malloc pero al parecer libera la memoria de la cadena que le pasa como parametro. Si no se inicializa a null antes de pasarsela, en algun bucle de getcwd da sigseg
	minishell->mini_home = getenv("HOME"); // no almacena en malloc
	minishell->input_pipes = NULL;
	minishell->cmds = NULL;
	minishell->cmd_path = NULL;
	minishell->env_path = NULL;
	minishell->or_infd = dup(STDIN_FILENO);
	rl_catch_signals = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	minishell;

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
				break ;
			add_history(minishell.input);
			ft_process_input(&minishell);
			/*inputsplit, splitpipe*/
			free(minishell.input);
		}
		ft_general_free(&minishell);
		return (printf("exit\n")); // pedirle a cristian que me diga como ponerlo en mi misma linea
	}
	printf("Error. Invalid arguments.\n");
	return (0);
}
