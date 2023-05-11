/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:24:01 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:24:04 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dst;

	i = -1;
	if (!str)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dst)
		return (NULL);
	while (str[++i])
		dst[i] = str[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strndup(const char *str, size_t n)
{
	char	*dst;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (n > len)
		n = len;
	dst = (char *)malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (NULL);
	dst[n] = '\0';
	while (n--)
		dst[n] = str[n];
	return (dst);
}

char	**ft_2dstrdup(const char **str)
{
	int		i;
	char	**dst;

	i = -1;
	if (!str)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_2dstrlen(str) + 1));
	if (!dst)
		return (NULL);
	while (str[++i])
		dst[i] = ft_strdup(str[i]);
	dst[i] = NULL;
	return (dst);
}
