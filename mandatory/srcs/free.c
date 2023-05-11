/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:41:44 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:41:47 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	ft_free_2dstr(char **str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			free(str[i]);
		free(str);
		str = NULL;
	}
}

void	ft_free_3dstr(char ***str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			ft_free_2dstr(str[i]);
		free(str);
		str = NULL;
	}
}

void	ft_general_free(t_mini *minishell)
{
	if (minishell->mini_env)
		ft_free_2dstr(minishell->mini_env);
	if (minishell->input_split)
		ft_free_2dstr(minishell->input_split);
	if (minishell->input)
		ft_free_str(minishell->input);
	if (minishell->curr_path)
		ft_free_str(minishell->curr_path);
}
