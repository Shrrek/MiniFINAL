/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-p <sperez-p@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:28:38 by sperez-p          #+#    #+#             */
/*   Updated: 2023/05/11 12:11:20 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	*ft_find_del(char *str, int quote, int *i, int *j)
{
	if (str[*i] == quote)
	{
		++(*i);
		while (str[*i] && str[(*i)] != quote)
		{
			str[*j] = str[*i];
			(*j)++;
			(*i)++;
		}
	}
	return (str);
}

void	ft_delete_quotes(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		ft_find_del(str, 34, &i, &j);
		ft_find_del(str, 39, &i, &j);
		if (str[i] != 34 && str[i] != 39)
		{
			str[j] = str[i];
			j++;
		}
	}
	str[j] = '\0';
}

void	ft_pass_quotes(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
}

static int	ft_check_quote_pair(const char *str, int quote, int *i)
{
	if (str[*i] == quote)
	{
		(*i)++;
		while (str[*i] && str[*i] != quote)
			(*i)++;
		if (str[*i] == quote)
			return (1);
		return (0);
	}
	return (1);
}

bool	ft_quote_pairs(char *str)
{
	int		i;
	int		quote_34;
	int		quote_39;
	bool	error;

	i = -1;
	error = false;
	quote_34 = 1;
	quote_39 = 1;
	while (str[++i])
	{
		quote_34 = ft_check_quote_pair(str, 34, &i);
		quote_39 = ft_check_quote_pair(str, 39, &i);
		if (!str[i])
			break ;
	}
	if (quote_34 == 0)
		printf("> MiniTabaqueros: unexpected EOF while looking\
		for matching `\"'\n");
	else if (quote_39 == 0)
		printf("> MiniTabaqueros: unexpected EOF while looking\
		for matching `''\n");
	else
		error = true;
	if (error == false)
		printf("MiniTabaqueros: syntax error: unexpected end of file\n");
	return (error);
}
