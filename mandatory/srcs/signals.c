/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:11:46 by jperales          #+#    #+#             */
/*   Updated: 2023/03/29 16:11:51 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT) //ctrl c
	{
		ft_putstr_fd(0, "\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		return ;
}

void	ft_child_signal_handler(int signal)
{
	if (signal == SIGINT)
		ft_putstr_fd(0, "\n", 0);
	if (signal == SIGQUIT)
		ft_putstr_fd(0, "Quit:\n", 0);
}
