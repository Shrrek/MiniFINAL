/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:12:35 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 12:12:38 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

bool	ft_is_redir(int c)
{
	return (c == '<' || c == '>');
}

/*
  Recorremos el input del usuario buscando cualquier tipo de redireccion.
  Segun encuentra una, comprueba si existe algun error:
	- Hay mas de 2 redirecciones del mismo tipo juntas
	- Hay espacios entre redirecciones

*/
bool	ft_parse_redir(t_mini *minishell)
{
	int		i;
	char	redir;

	i = 0;
	while (minishell->input[i])
	{
		if (ft_is_redir(minishell->input[i]))
		{
			redir = minishell->input[i];
			i++;
			if (minishell->input[i] == ' ')
			{
				while (minishell->input[i] && minishell->input[i] == ' ')
					i++;
				if (!minishell->input[i])
				{
					printf("Minitabaqueros: syntax error near unexpected token `newline'");
					return (false);
				}
				if (ft_is_redir(minishell->input[i]))
				{
					printf("Minitabaqueros: syntax error near unexpected token {redir}");
					return (false);
				}
			}
			else if (redir == minishell->input[i])
			{
				if (redir == minishell->input[i + 1])
				{
					printf("Minitabaqueros: syntax error near unexpected token {redir}");
					return (false);
				}
			}
		}
		i++;
	}
	return (true);
}
