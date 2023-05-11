/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:56:37 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:56:41 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
 * Comprueba que el primer pipe del input tenga un comando que procesar.
 * Si lo primero que se encuentra es un pipe, o si solo encuentra espacios
 * hasta el primer pipe devuelve 1 denotando el error.
 *
 */
static int	ft_start_pipe(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '|')
		return (1);
	while (input[i] && input[i] == ' ')
	{
		i++;
		if (input[i] == '|')
			return (1);
	}
	return (0);
}

/*
 *
 *
 *
 */
static int	ft_end_pipe(char *input)
{
	int	i;

	i = 0;
	if (input[ft_strlen(input)])
		return (1);
	while (input[i])
	{
		i++;
		if (input[i] == '|')
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i])
				return (1);
		}
	}
	return (0);
}

/*
 * Funcion que comprueba que no exista ningun pipe sin contenido en mitad del input del usuario
 * En primer lugar recorre la cadena hasta llegar al primer pipe. 
 *
 */
static int	ft_middle_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i++;
		if (input[i] == '|')
		{
			i++;
			if (input[i] == '|')
				return (1);
			while (input[i] == ' ' && input[i])
			{
				i++;
				if (input[i] == '|')
					return (1);
			}
		}
	}
	return (0);
}

/*
 * Funcion que comprueba si hay algun error de pipes en el input del usuario.
 * Comprueba que no haya ningun pipe sin contenido que pipear y muestra su mensaje
 * de error correspondiente.
 */
bool	ft_parse_pipes(char *str)
{
	bool	error;

	error = false;
	if (ft_start_pipe(str) || ft_middle_pipes(str))
		printf("MiniTabaqueros: syntax error near unexpected token '|'\n");
	else if (ft_end_pipe(str))
		printf("> MiniTabaqueros: syntax error: unexpected end of file\n");
	else
		error = true;
	return (error);
}
