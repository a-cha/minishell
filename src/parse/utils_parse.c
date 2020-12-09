/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:37:33 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 14:48:16 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Finds first linebreak (pipe / semicolon) and returns index of it's position
** If there are no linebreaks returns -1
*/

int			is_linebreak(const char *line)
{
	size_t	res;
	size_t	s;

	res = ft_strlen(line);
	if ((s = is_symb(line, ';')) < res)
		res = s;
	if ((s = is_symb(line, '|')) < res)
		res = s;
	return (res == ft_strlen(line) ? -1 : (int)res);
}

/*
** Finds first quotation mark and returns index of it's position
** If there are no quotation marks returns -1
*/

int			is_quotmark(const char *line)
{
	size_t	res;
	size_t	s;

	res = ft_strlen(line);
	if ((s = is_symb(line, '"')) < res)
		res = s;
	if ((s = is_symb(line, '\'')) < res)
		res = s;
	return (res == ft_strlen(line) ? -1 : (int)res);
}

/*
** Returns pointer to first sign (pipe / semicolon / quotation mark)
*/

size_t		catch_first_sign(const char *str, t_data *part, char *r)
{
	int		min;
	int		res;

	min = ft_strlen(str);
	if ((res = is_linebreak(str)) != -1 && res < min)
		min = res;
	if ((res = is_quotmark(str)) != -1 && res < min)
		min = res;
	if (str[min] == ';')
		part->type = ';';
	else if (str[min] == '|')
		part->type = '|';
	else
		part->type = '\0';
	if (str[min] == '\'' || str[min] == '"')
		*r = str[min];
	else
		*r = '\0';
	return (min);
}
