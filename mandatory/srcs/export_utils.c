/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:25:07 by jperales          #+#    #+#             */
/*   Updated: 2023/03/29 16:25:10 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	ft_isin_intarr(int nbr, int *nbr_lst, size_t lst_len)
{
	while (lst_len--)
	{
		if (nbr == nbr_lst[lst_len])
			return (1);
	}
	return (0);
}

static int	ft_get_smaller_stridx(const char **str,
	int *nbr_lst, size_t lst_len)
{
	int	i;
	int	j;
	int	index;

	index = 0;
	while (ft_isin_intarr(index, nbr_lst, lst_len) == 1)
		index++;
	i = index;
	while (str[++i] != NULL)
	{
		j = 0;
		if (ft_isin_intarr(i, nbr_lst, lst_len) == 1)
			continue ;
		while (str[index][j] == str[i][j])
			j++;
		if (str[index][j] > str[i][j])
			index = i;
	}
	return (index);
}

int	*ft_get_2dstr_order(const char **str)
{
	int		*pos_lst;
	size_t	len;
	int		lst_len;

	lst_len = 0;
	len = ft_2dstrlen((char **)str);
	pos_lst = (int *)malloc(sizeof(int) * (len));
	if (!pos_lst)
		return (NULL);
	while (len--)
	{
		pos_lst[lst_len] = ft_get_smaller_stridx(str, pos_lst, lst_len);
		lst_len++;
	}
	return (pos_lst);
}
