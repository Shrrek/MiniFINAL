/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:10:36 by jperales          #+#    #+#             */
/*   Updated: 2023/05/23 18:10:39 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_process_quote(const char *str, int *i, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	(*i)++;
}

void	ft_process_spaces(const char *str, int *i, int *start, char c)
{
	while (str[*i] && str[*i] == c)
	{
		(*i)++;
		*start = *i;
	}
}
