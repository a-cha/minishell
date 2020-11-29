/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:00:45 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 20:43:57 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_redir(const char *line, char *r)
{
	size_t	res;
	size_t	s;

	*r = 0;
	res = ft_strlen(line);
	if ((s = is_symb(line, REDIR_L)) < res)
	{
		res = s;
		*r = *(line + res);
	}
	if ((s = is_symb(line, REDIR_R)) < res)
	{
		res = s;
		*r = *(line + res);
		if (!(ft_strncmp(line + s, ">>", 2)))
			*r = 'd';
	}
	return (res == ft_strlen(line) ? -1 : (int)res);
}

int			redirections(char *line, t_data *part)
{
	char 	r;
	size_t	i;

	i = 0;

	return ();
}

//{
//	size_t	res;
//	size_t	s;
//
//	res = ft_strlen(line);
//	if ((s = is_symb(line, SEMICOLON)) < res)
//	res = s;
//	if ((s = is_symb(line, PIPE)) < res)
//	res = s;
//	return (res == ft_strlen(line) ? -1 : (int)res);
//}