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
	while (i < len && str[start + i] == ' ')
		i++;
	if (len != 0 && str[start + i] != ' ')
		return (0);
	return (1);
}

static char	*ret_token(char t, int n)
{
	char	*weird;

	weird = ft_calloc(n + 1, sizeof(char));
	weird[0] = t;
	if (n == 2)
		weird[1] = t;
	return (weird);
}

static char	*is_blank(const char *str, int start, int len)
{
	int		s;

	if ((space(str, start, len)))
	{
		if ((s = is_linebreak(str + start + len + 1)) >= 0)
		{
			if (!space(str, start + len + 1, s))
				return (ret_token(*(str + start + len), 1));
			else if (*(str + start + len) != *(str + start + len + 1 + s))
				return (ret_token(*(str + start + len), 1));
			else
				return (ret_token(*(str + start + len), 2));
		}
		else if (*(str + start + len) == *(str + start + len - 1))
			return (ret_token(*(str + start + len), 2));
		else
			return (ret_token(*(str + start + len), 1));
	}
	return (NULL);
}

int			weird_cases(const char *line)
{
	size_t	i;
	int		s;
	char	*weird;

	i = 0;
	while ((s = is_linebreak(line + i)) >= 0)
	{
		if ((weird = is_blank(line, i, s)))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
			ft_putstr_fd(weird, 1);
			ft_putstr_fd("'\n", 1);
			free_memory(weird);
			return (1);
		}
		i += s + 1;
	}
	return (0);
}
