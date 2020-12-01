/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_and_quoters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:47:27 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/29 22:47:28 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if symbol has escaped (or not escaped)
*/

static void		escape_symb_line(char *dup)
{
	size_t		i;
	size_t		r;

	i = -1;
	while (dup[++i])
	{
		if (dup[i] == '\\')
		{
			r = -1;
			while (dup[i + ++r])
				dup[i + r] = dup[i + r + 1];
		}
	}
}

static void		escape_symb_quot(char *dup)
{
	size_t		i;
	size_t		r;

	i = -1;
	while (dup[++i])
	{
		if (dup[i] == '\\' &&
			(dup[i + 1] == '\\' || dup[i + 1] == '\"' || dup[i + 1] == '$'))
		{
			r = -1;
			while (dup[i + ++r])
				dup[i + r] = dup[i + r + 1];
		}
	}
}

/*
** Handle line & quot part
*/

char		**handle_line(char *line, t_data *part)
{
	char 	*dup;
	char 	**ret;
//	crutch for redirections
//	char	r;

	dup = handle_env(line, part);
	free_memory(line);
	redirections(dup, part);
	escape_symb_line(dup);
	ret = ft_split(dup, ' ');
	free_memory(dup);
	return (ret);
}

char		*handle_quot(char *line, t_data *part)
{
	char 	*dup;

	dup = handle_env(line, part);
	free_memory(line);
	escape_symb_quot(dup);
	return (dup);
}
