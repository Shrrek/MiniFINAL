/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-p <sperez-p@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:56:37 by sperez-p          #+#    #+#             */
/*   Updated: 2023/05/11 11:56:41 by sperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static bool	ft_start_pipe(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '|')
		return (true);
	while (input[i] && input[i] == ' ')
	{
		if (input[i] == 34 || input[i] == 39)
			ft_pass_quotes(input, &i);
		i++;
		if (input[i] == '|')
			return (true);
	}
	return (false);
}

static int	ft_end_pipe(char *input)
{
	int	i;

	i = 0;
	if (input[ft_strlen(input)])
		return (1);
	while (input[i])
	{
		i++;
		if (input[i] == '|')
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i])
				return (1);
		}
	}
	return (0);
}

static int	ft_middle_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			ft_pass_quotes(input, &i);
		i++;
		if (input[i] == '|')
		{
			i++;
			if (input[i] == '|')
				return (1);
			while (input[i] && input[i] == ' ')
			{
				i++;
				if (input[i] == '|')
					return (1);
			}
		}
	}
	return (0);
}

bool	ft_parse_pipes(char *str)
{
	bool	error;

	error = false;
	if (ft_start_pipe(str) || ft_middle_pipes(str))
		printf("MiniTabaqueros: syntax error near unexpected token '|'\n");
	else if (ft_end_pipe(str))
		printf("> MiniTabaqueros: syntax error: unexpected end of file\n");
	else
		error = true;
	return (error);
}
