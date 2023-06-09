/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:09:43 by jperales          #+#    #+#             */
/*   Updated: 2023/05/23 18:09:46 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	ft_intlen(int n)
{
	int	n_len;

	n_len = 0;
	if (n == 0)
		n_len++;
	if (n < 0)
	{
		n *= -1;
		n_len++;
	}
	while (n > 0)
	{
		n /= 10;
		n_len++;
	}
	return (n_len);
}

static char	*ft_charconv(char *dest, int n, int n_len)
{
	if (n == 0)
		*dest = 48;
	if (n < 0)
	{
		*dest = 45;
		n *= -1;
	}
	while (n > 0)
	{
		*(dest + n_len--) = 48 + (n % 10);
		n /= 10;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		n_len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	n_len = ft_intlen(n);
	dest = (char *)malloc(sizeof(char) * n_len + 1);
	if (!dest)
		return (NULL);
	*(dest + n_len--) = '\0';
	dest = ft_charconv(dest, n, n_len);
	return (dest);
}
