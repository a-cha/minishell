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

//	replace to is_symb
static int	space(const char *str, int start, int len)
{
	size_t	i;

	i = 0;
	while (i < len && is_symb(&str[start + i], ' ') && is_symb(&str[start + i], ';')
	&& str[start + i] != '|' && str[start + i] != '>' && str[start + i] != '<')
		i++;
	if (str[start + i] && len != 0 && str[start + i] != ' ' && str[start + i] != ';'
	&& str[start + i] != '|' && str[start + i] != '>' && str[start + i] != '<')
		return (0);
	return (1);
}
//		while (i < len && is_symb(&str[start + i], ' ') && is_symb(&str[start + i], ';')

static int	ret_token(char t, int n, char *str)
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
	char	flag;
	char	*m;

	flag = 0;
	c = -1;
	while (str[++c] && str[c] == ' ')
		;
	if (str[c] && (str[c] != ' ' && str[c] != '>' && str[c] != '<'))
		flag = 1;
	if (flag == 0)
	{
		if (!(m = ft_strdup("newline")))
			return (-1);
		return (ret_token(0, 0, m));
	}
	return (0);
}

char 		is_in_quots(const char *line, size_t n)
{
	size_t	i;
	int 	s;
	int 	f;

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

int			set_status(int stat)
{
	last_status = stat;
	return (1);
}

int 		is_closed_pipe(const char *line)
{
	char	*pipe;
	char	*dup;

	if (!(dup = ft_strdup(line)))
		return (-1);
	if ((pipe = ft_strrchr(dup, '|')))
	{
		*pipe = '\0';
		if (!is_in_quots(dup, pipe - dup))
			if (space(dup, (int)(pipe - dup), ft_strlen(dup + (int)(pipe - dup))))
			{
				free_memory(dup);
				if (!(dup = ft_strdup("newline")))
					return (-1);
				return (ret_token(0, 0, dup));
			}
	}
	free_memory(dup);
	return (0);
}

int			weird_cases(const char *line)
{
	size_t	i;
	int		s;
	char	r;
	int 	ret;

	i = 0;
	while ((s = is_redir(line + i, &r)) >= 0)
	{
		i += s + 1 + (r == 'd');
		if (!is_in_quots(line, i - 1))
			if ((ret = is_wrong_redir(line + i)))
				return (ret < 0 ? -1 : set_status(258));
	}
	i = 0;
	while ((s = is_linebreak(line + i)) >= 0)
	{
		if (!is_in_quots(line, i + s))
			if ((is_blank(line, i, s)))
				return (set_status(258));
		i += s + 1;
	}
	if ((ret = is_closed_pipe(line)))
		return (ret < 0 ? -1 : set_status(258));
	return (0);
}
