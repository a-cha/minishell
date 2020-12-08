/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:34:12 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/28 16:34:17 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees null-terminated array
*/
void		ft_arrayfree(char **array)
{
	size_t	i;

	i = -1;
	while (array[++i])
		free_memory(array[i]);
	free_memory(array);
}

/*
** Counts lines in null-terminated array
*/
int			ft_arrlen(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*
** Returns max value
*/
static int	max(int n1, int n2)
{
	return (n1 > n2 ? n1 : n2);
}

static int	space_flag(char **res, char **arr1, char **arr2, int l)
{
	res[0] = arr1[l - (l != 0)];
	if (!(arr1[l - (l != 0)] = ft_strjoin(arr1[l - (l != 0)], arr2[0])))
	{
		free_memory(res);
		return (-1);
	}
	free_memory(res[0]);
	return (0);
}

/*
** Joins two null-terminated arrays and free pointers to them
*/
char		**ft_arrjoin_pro(char **arr1, char **arr2, char flag)
{
	size_t	i;
	int 	l;
	char	**res;

	if (!*arr1)
	{
		free_memory(arr2);
		return (arr2);
	}
	if (!*arr2)
	{
		free_memory(arr1);
		return (arr1);
	}
	l = ft_arrlen(arr1);
	if (!(res = ft_calloc(8,
				max(l + ft_arrlen(arr2) + (flag == ' ') + !(l), 2))))
		return (NULL);
	if (flag != ' ')
		if ((space_flag(res, arr1, arr2, l)) < 0)
			return (NULL);
	i = -1;
	while (++i < l + !(l))
		res[i] = arr1[i];
	l != 0 ? free_memory(arr1[i]) : 1;
	i = !(l) ? 0 : i - 1;
	while (arr2[++i - (l != 0 ? l : 1) + (flag != ' ')] && (*arr2))
		res[i] = arr2[i - (l != 0 ? l : 1) + (flag != ' ')];
	free_memory(arr1);
	free_memory(arr2);
	return (res);
}
