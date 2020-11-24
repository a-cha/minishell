/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:37:33 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 22:05:12 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** Counts lines in null-terminated array
*/
size_t	ft_arraylen(void **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*
** Frees null-terminated array
*/
char	**ft_arrayfree(void **array)
{
	size_t i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
	return (NULL);
}

/*
** Joins two null-terminated arrays and free pointers to them
*/
void	**ft_arrayjoin(void **array1, void **array2)
{
	size_t	i;
	size_t	len;
	void	**res;

	len = ft_arraylen(array1);
	if (!(res = malloc(sizeof(void *) * (len + ft_arraylen(array2) + 1))))
		return (NULL);
	i = -1;
	while (array1[++i])
		res[i] = array1[i];
	free(array1[i]);
	array1[i] = NULL;
	i--;
	while (array2[++i - len])
		res[i] = array2[i - len];
	res[i] = array2[i - len];
	free(array1);
	array1 = NULL;
	free(array2);
	array2 = NULL;
	return (res);
}

/*
** Frees pointer and turns it to NULL
*/
void	free_memory(void *memory)
{
	free(memory);
	memory = NULL;
}

/*
** Find out if symbol is escaped
*/
size_t	is_escaped(const char *line, size_t i)
{
	size_t	n;

	n = 0;
	if (i != 0)
	{
		while ((i--) && line[i] == '\\')
			n++;
	}
	return (n % 2);
}

/*
** Finds first not escaped needed symbol in line
*/
int		is_symb(const char *line, char c)
{
	size_t	i;
	size_t	min;
	char	*symb;

	i = 0;
	min = ft_strlen(line);
	while ((symb = ft_strchr(line + i, c)))
	{
		if (min > symb - line && !(is_escaped(line, symb - line)))
		{
			min = symb - line;
			break ;
		}
		i += symb - line + 1;
	}
	return (min == ft_strlen(line) ? -1 : (int)min);
}
