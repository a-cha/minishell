/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weird_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 17:15:39 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/29 17:15:41 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_blank(const char *str, int start, int len)
{
	int		s;

	if ((space(str, start, len)))
	{
		if ((s = is_linebreak(str + start + len + 1)) >= 0)
		{
			if ((!space(str, start + len + 1, s)) ||
					*(str + start + len) != *(str + start + len + 1 + s))
				return (ret_token(*(str + start + len), 1, NULL));
			else
				return (ret_token(*(str + start + len), 2, NULL));
		}
		else if (*(str + start + len) == *(str + start + len - 1))
			return (ret_token(*(str + start + len), 2, NULL));
		else
			return (ret_token(*(str + start + len), 1, NULL));
	}
	return (0);
}

static int	is_wrong_redir(const char *str)
{
	size_t	c;
	char	*m;

	c = -1;
	while (str[++c] && !is_symb(&str[c], ' '))
		;
	if (is_symb(&str[c], ' ') &&
	is_symb(&str[c], ';') && is_symb(&str[c], '|'))
		;
	else
		return (ret_token(*(str + c), 1, NULL));
	if (str[c] && is_symb(&str[c], ' ') &&
	is_symb(&str[c], '>') && is_symb(&str[c], '<'))
		;
	else
	{
		if (!(m = ft_strdup("newline")))
			return (-1);
		return (ret_token(0, 0, m));
	}
	return (0);
}

static char	is_in_quots(const char *line, int n)
{
	size_t	i;
	int		s;
	int		f;

	i = 0;
	while ((s = is_quotmark(line + i)) >= 0)
	{
		if ((f = is_closed_quot(line, *(line + i + s + 1))) >= 0)
		{
			if (s < n && n < f)
				return (1);
		}
		else
			return (1);
		i += s + f + 2;
	}
	return (0);
}

static int	is_closed_pipe(const char *line)
{
	char	*pipe;
	char	*dup;

	if (!(dup = ft_strdup(line)))
		return (-1);
	if ((pipe = ft_strrchr(dup, '|')) && !is_symb(pipe, '|'))
	{
		if (!is_in_quots(dup, (int)(pipe - dup)))
			if (space(dup, (int)(pipe - dup) + 1,
						ft_strlen(dup + (int)(pipe - dup + 1))))
			{
				free_memory(dup);
				if (!(dup = ft_strdup("newline")))
					return (-1);
				return (ret_token(0, 0, dup));
			}
		*pipe = '\0';
	}
	free_memory(dup);
	return (0);
}

int			weird_cases(const char *line)
{
	int 	i;
	int		s;
	char	r;
	int		ret;

	i = 0;
	while ((s = is_linebreak(line + i)) >= 0)
	{
		if (!is_in_quots(line, i + s))
			if ((is_blank(line, i, s)))
				return (set_status(258));
		i += s + 1;
	}
	i = 0;
	while ((s = is_redir(line + i, &r)) >= 0)
	{
		i += s + 1 + (r == 'd');
		if (!is_in_quots(line, i - 1))
			if ((ret = is_wrong_redir(line + i)))
				return (ret < 0 ? -1 : set_status(258));
	}
	if ((ret = is_closed_pipe(line)))
		return (ret < 0 ? -1 : set_status(258));
	return (0);
}
