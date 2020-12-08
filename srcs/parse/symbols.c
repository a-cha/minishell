/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 20:37:59 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/29 20:38:04 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Find out if quotation marks closed
*/

int				is_closed_quot(const char *line, char r)
{
	char		*tmp;
	int			f;

	f = -2;
	if (r == '\'')
	{
		if ((tmp = ft_strchr(line, r)))
			f = (int)(tmp - line);
		else
			return (-1);
	}
	else if (r == '"')
		if ((f = is_symb(line, r)) == -1)
			return (-1);
	return (f);
}

/*
** Find out if symbol is escaped
*/

static size_t	is_esc(const char *line, size_t i)
{
	size_t		n;

	n = 0;
	if (i != 0)
		while ((i--) && line[i] == '\\')
			n++;
	return (n % 2);
}

/*
** Finds first not escaped needed symbol in line
*/

int				is_symb(const char *line, char c)
{
	size_t		i;
	size_t		min;
	char		*symb;

	i = 0;
	min = ft_strlen(line);
	while ((symb = ft_strchr(line + i, c)))
	{
		if (min > symb - line && !(is_esc(line, symb - line)))
		{
			min = symb - line;
			break ;
		}
		i += symb - line + 1;
	}
	return (min == ft_strlen(line) ? -1 : (int)min);
}
