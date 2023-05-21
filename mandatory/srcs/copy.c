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
	dst = (char *)malloc(sizeof(char) * ft_strlen((char *)str) + 1);
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
	len = ft_strlen((char *)str);
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
	dst = (char **)malloc(sizeof(char *) * (ft_2dstrlen((char **)str) + 1));
	if (!dst)
		return (NULL);
	while (str[++i])
		dst[i] = ft_strdup(str[i]);
	dst[i] = NULL;
	return (dst);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstl;
	size_t	srcl;
	size_t	i;

	dstl = ft_strlen(dst);
	srcl = ft_strlen((char *)src);
	i = dstl;
	if (dstl >= dstsize)
		return (dstsize + srcl);
	while (dstl < dstsize - 1 && *src)
		*(dst + dstl++) = *src++;
	*(dst + dstl) = '\0';
	return (i + srcl);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	if (len == 0)
		return (dst);
	while (*src && --len)
		*dst++ = *src++;
	while (--len)
		*dst++ = '\0';
	*dst = '\0';
	return (dst);
}
