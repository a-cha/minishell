/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:47:14 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/24 11:47:17 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_count(const char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
			i++;
		if (str[i - 1] != c)
			count++;
	}
	return (count * 2);
}

static int	char_count(const char *str, char c)
{
	int k;

	k = 0;
	while (str[k] != c && str[k])
		k++;
	return (k);
}

static char	**free_d_array(char **terminated_array)
{
	size_t i;

	i = -1;
	while (terminated_array[++i])
		free(terminated_array[i]);
	free(terminated_array);
	return (NULL);
}

char		**ft_split_pro(char const *s, char c)
{
	int		j;
	int		k;
	char	**res;

	if (!(res = (char **)malloc(sizeof(char *) * (words_count(s, c) + 1))))
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!(*s))
			break ;
		k = char_count(s, c);
		if (!(res[j++] = ft_substr(s, 0, k)))
			return (free_d_array(res));
		if (!(res[j++] = ft_substr(&c, 0, 1)))
			return (free_d_array(res));
		s += k;
	}
	free(res[--j]);
	res[j] = 0;
	return (res);
}

