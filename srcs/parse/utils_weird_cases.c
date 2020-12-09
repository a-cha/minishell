/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_weird_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 17:15:39 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/29 17:15:41 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Find out if part of the line is empty
*/

int			space(const char *str, int start, int len)
{
	int		i;

	i = 0;
	while (i < len && !is_symb(&str[start + i], ' '))
		i++;
	if (str[start + i] && len != 0 && is_symb(&str[start + i], ' ') &&
		is_symb(&str[start + i], ';') && is_symb(&str[start + i], '|')
		&& is_symb(&str[start + i], '>') && is_symb(&str[start + i], '<'))
		return (0);
	return (1);
}

/*
** Print error message and return needed value
*/

int			ret_token(char t, int n, char *str)
{
	char	*weird;

	if (!str)
	{
		if (!(weird = ft_calloc(n + 1, sizeof(char))))
			return (-1);
		weird[0] = t;
		if (n == 2)
			weird[1] = t;
	}
	else
		weird = str;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(weird, 2);
	ft_putstr_fd("'\n", 2);
	free_memory(weird);
	return (1);
}

/*
** Set last operation status and return needed value
*/

int			set_status(int stat)
{
	g_last_status = stat;
	return (1);
}
