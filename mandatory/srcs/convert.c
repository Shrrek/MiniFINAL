/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:22:27 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:22:30 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_atoi(const char *str)
{
	int		result;
	ssize_t	sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		result = (*str++ - 48) + (result * 10);
	return (result * sign);
}

static int	ft_2dcontlen(char **str)
{
	int	len;
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	if (!str)
		return (0);
	len = ft_2dstrlen(str);
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			count++;
		if (i < len)
			count++;
	}
	return (count);
}

char	*ft_2dtostr(char **str)
{
	char	*dst;
	int		i;
	int		j;
	int		k;
	int		len;

	len = ft_2dstrlen(str);
	if (!str)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (ft_2dcontlen(str) + 1));
	if (!dst)
		return (NULL);
	i = -1;
	k = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			dst[++k] = str[i][j];
		if (i != len)
			dst[++k] = ' ';
	}
	dst[++k] = '\0';
	return (dst);
}
