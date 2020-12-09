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
** If there are escaped symbols in string, put string in order
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

char			**handle_line(const char *line, int s, int f, t_data *part)
{
	char		*dup;
	char		*tmp;
	char		**ret;

	if (!(dup = ft_substr(line, s, f)))
		ft_exit(part, EXIT_FAILURE);
	tmp = dup;
	dup = handle_env(dup, part);
	free_memory(tmp);
	redirections(dup, part);
	escape_symb_line(dup);
	if (!(ret = ft_split(dup, ' ')))
		ft_exit(part, EXIT_FAILURE);
	free_memory(dup);
	return (ret);
}

char			*handle_quot(char *line, t_data *part)
{
	char		*dup;

	dup = handle_env(line, part);
	free_memory(line);
	escape_symb_quot(dup);
	return (dup);
}
