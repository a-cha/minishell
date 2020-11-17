/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarnati <acarnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 15:31:12 by acarnati          #+#    #+#             */
/*   Updated: 2020/11/17 08:09:37 by acarnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		chisl_word(const char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i] && (str[i] != c))
		{
			while (str[i] && (str[i] != c))
				i++;
			j++;
		}
	}
	return (j);
}

static size_t	ft_len(const char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static char		**ft_free(char **arr, int j)
{
	while (j-- > 0)
		free(arr[j]);
	free(arr);
	return (NULL);
}

char			**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**str;

	i = 0;
	j = 0;
	if (!s || !(str = malloc(sizeof(char*) * (chisl_word(s, c) + 1))))
		return (NULL);
	while ((k = 0) || s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		if (s[i])
		{
			k = 0;
			if (!(str[j] = malloc(sizeof(char) * (ft_len(s + i, c) + 1))))
				return (ft_free(str, j));
			while (s[i] && (s[i] != c))
				str[j][k++] = s[i++];
			str[j++][k] = 0;
		}
	}
	str[j] = 0;
	return (str);
}
