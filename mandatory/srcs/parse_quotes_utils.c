/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:58:19 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:58:22 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static	void	ft_process_string_aux(const char *str, int *i, char c)
{
	while (str[*i] && str[*i] != c && str[*i] != 34 && str[*i] != 39)
		(*i)++;
}

static char	**ft_process_string(char **dest, const char *str, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = -1;
	start = 0;
	while (str[i])
	{
		ft_process_spaces(str, &i, &start, c);
		if (!str[i])
			break ;
		if (str[i] && (str[i] == 34 || str[i] == 39))
			ft_process_quote(str, &i, str[i]);
		if (str[i] && str[i] != c)
			ft_process_string_aux(str, &i, c);
		if (!str[i] || str[i] == c)
		{
			dest[++j] = ft_strndup(&str[start], i - start);
			start = i;
		}
	}
	dest[++j] = NULL;
	return (dest);
}

static size_t	ft_line_counter(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			while (str[i] && str[i] != c)
			{
				if (str[i] == 34 || str[i] == 39)
					ft_process_quote(str, &i, str[i]);
				while (str[i] && str[i] != c && str[i] != 34 && str[i] != 39)
					i++;
			}
		}
		if (!str[i] || str[i] == c)
			count++;
	}
	return (count);
}

char	**ft_split_input(char *str, char c)
{
	char	**dest;

	if (!str)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (ft_line_counter(str, c) + 1));
	if (!dest)
		return (NULL);
	ft_process_string(dest, str, c);
	return (dest);
}
