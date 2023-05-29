/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:53:08 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:53:12 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	**ft_fill_split(char **dst, char *str)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = -1;
	start = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			ft_pass_quotes(str, &i);
		else if (str[i] == '|')
		{
			dst[++j] = ft_strndup(&str[start], i - start);
			start = i + 1;
		}
		i++;
	}
	dst[++j] = ft_strndup(&str[start], i - start);
	dst[++j] = NULL;
	return (dst);
}

static size_t	ft_pipe_counter(char *str)
{
	size_t	count;
	int		i;

	i = 0;
	count = 1;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			ft_pass_quotes(str, &i);
		else if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	**ft_split_pipes(char *str)
{
	char	**dst;

	if (!str)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_pipe_counter(str) + 1));
	if (!dst)
		return (NULL);
	ft_fill_split(dst, str);
	return (dst);
}
