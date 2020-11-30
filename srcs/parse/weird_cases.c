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

static int	space(const char *str, int start, int len)
{
	size_t	i;

	i = 0;
	while (i < len && str[start + i] == ' ' && str[start + i] != ';'
	&& str[start + i] != '|' && str[start + i] != '>' && str[start + i] != '<')
		i++;
	if (len != 0 && str[start + i] != ' ' && str[start + i] != ';'
	&& str[start + i] != '|' && str[start + i] != '>' && str[start + i] != '<')
		return (0);
	return (1);
}

static int	ret_token(char t, int n, char *str)
{
	char	*weird;

	if (!str)
	{
		weird = ft_calloc(n + 1, sizeof(char));
		weird[0] = t;
		if (n == 2)
			weird[1] = t;
	}
	else
		weird = str;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(weird, 1);
	ft_putstr_fd("'\n", 1);
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

	flag = 0;
	c = -1;
	while (str[++c] && str[c] == ' ')
		;
	if (str[c] && (str[c] != ' ' && str[c] != '>' && str[c] != '<'))
		flag = 1;
	if (flag == 0)
		return (ret_token(0, 0, ft_strdup("newline")));
	return (0);
}

int			weird_cases(const char *line)
{
	size_t	i;
	int		s;
	char	r;

	i = 0;
	while ((s = is_redir(line + i, &r)) >= 0)
	{
		i += s + 1 + (r == 'd');
		if ((is_wrong_redir(line + i)))
			return (1);
	}
	i = 0;
	while ((s = is_linebreak(line + i)) >= 0)
	{
		if ((is_blank(line, i, s)))
			return (1);
		i += s + 1;
	}
	return (0);
}
