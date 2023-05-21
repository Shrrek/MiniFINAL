/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:20:19 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:20:22 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (0);
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, int n)
{
	if (!str1 || !str2)
		return (1);
	while (*str1 && *str2 && --n > 0)
	{
		if ((unsigned char)*str1 != (unsigned char)*str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
