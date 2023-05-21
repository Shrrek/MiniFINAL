/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:12:35 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 12:12:38 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static bool	ft_is_redir(char c, char *redir)
{
	bool	is_redir;

	is_redir = false;
	if (c == '<' || c == '>')
	{
		*redir = c;
		is_redir = true;
	}
	return (is_redir);
}

static bool	ft_check_begin_redir(t_mini *minishell, char *redir, int start)
{
	if (minishell->input[start] == '|')
		start++;
	while (minishell->input[start] && minishell->input[start] == ' ')
		start++;
	if (ft_is_redir(minishell->input[start], redir))
		return (true);
	return (false);
}

static bool	ft_check_middle_redir(t_mini *minishell, int i, char redir)
{
	i++;
	if (minishell->input[i] == redir)
		i++;
	while (minishell->input[i] && minishell->input[i] == ' ')
		i++;
	if (!minishell->input[i] || ft_is_redir(minishell->input[i], &redir)
		|| minishell->input[i] == '|')
		return (true);
	while (minishell->input[i] && minishell->input[i] != '|'
		&& !ft_is_redir(minishell->input[i], &redir)
		&& minishell->input[i] != ' ')
	{
		if (minishell->input[i] == 34 || minishell->input[i] == 39)
		{
			ft_pass_quotes(minishell->input, &i);
			i++;
		}
		else
			i++;
	}
	return (false);
}

bool	ft_parse_redir(t_mini *minishell)
{
	int		start;
	char	redir;
	bool	redir_error;
	int		i;

	start = 0;
	i = 0;
	while (minishell->input[i])
	{
		if (minishell->input[i] == 34 || minishell->input[i] == 39)
			ft_pass_quotes(minishell->input, &i);
		if (minishell->input[i] == '|')
			start = i;
		if (ft_is_redir(minishell->input[i], &redir))
		{
			redir_error = ft_check_begin_redir(minishell, &redir, start);
			if (redir_error == true)
			{
				ft_putstr_fd(0, "Minitabaqueros: syntax error near unexpected token `newline'\n", 0);
				return (false);
			}
			redir_error = ft_check_middle_redir(minishell, i, redir);
			if (redir_error == true)
			{
				ft_putstr_fd(0, "Minitabaqueros: syntax error near unexpected token `", 0);
				write(0, &redir, 1);
				ft_putstr_fd(0, "'\n", 0);
				return (false);
			}
		}
		i++;
	}
	return (true);
}
