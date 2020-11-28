/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:37:33 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 14:48:16 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees pointer and turns it to NULL
*/
void	free_memory(void *memory)
{
	free(memory);
	memory = NULL;
}

/*
** Frees null-terminated array
*/
void	ft_arrayfree(char **array)
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
}

/*
** Counts lines in null-terminated array
*/
int		ft_arrlen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int 	max(int n1, int n2)
{
	return (n1 > n2 ? n1 : n2);
}

/*
** Joins two null-terminated arrays and free pointers to them
*/
int 	space_flag(char **res, char **arr1, char **arr2, int l, char flag)
{
	if (flag != ' ')
	{
		res[0] = arr1[l - (l != 0)];
		if (!(arr1[l - (l != 0)] = ft_strjoin(arr1[l - (l != 0)], arr2[0])))
		{
			free_memory(res);
			return (-1);
		}
		free_memory(res[0]);
	}
	return (0);
}

char	**ft_arrjoin_pro(char **arr1, char **arr2, char flag)
{
	size_t	i;
	int 	l;
	char	**res;

	if (!*arr1)
		return (arr2);
	if (!*arr2)
		return (arr1);
	l = ft_arrlen(arr1);
//
//	int t = max(l + ft_arrlen(arr2) + (flag == ' ') + !(l), 2);
	if (!(res = ft_calloc(8,
					max(l + ft_arrlen(arr2) + (flag == ' ') + !(l), 2))))
		return (NULL);
	if ((space_flag(res, arr1, arr2, l, flag)) == -1)
		return (NULL);
//	if (flag != ' ')
//	{
//		res[0] = arr1[l - (l != 0)];
//		if (!(arr1[l - (l != 0)] = ft_strjoin(arr1[l - (l != 0)], arr2[0])))
//			return (NULL);
//		free_memory(res[0]);
//	}
	i = -1;
	while (++i < l + !(l))
		res[i] = arr1[i];
	l != 0 ? free_memory(arr1[i]) : 1;
	i = !(l) ? 0 : i - 1;
//
//	t = (l != 0 ? l : 1) + (flag != ' ');
	while (arr2[++i - (l != 0 ? l : 1) + (flag != ' ')] && (*arr2))
		res[i] = arr2[i - (l != 0 ? l : 1) + (flag != ' ')];
	free_memory(arr1);
	free_memory(arr2);
	return (res);
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

/*
** Checks if symbol has escaped (or not escaped)
*/
void	escape_symb_line(char *dup)
{
	size_t	i;
	size_t	r;

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

void	escape_symb_quot(char *dup)
{
	size_t	i;
	size_t	r;

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

void	reset_t_data(t_data *data)
{
	if (data->args)
		ft_arrayfree(data->args);
	data->args = (char **)ft_calloc(1, sizeof(char **));
	data->len = -1;
//	need to utochnit'
	data->infile = 0;
	data->outfile = 1;
}

//	remove
void 	print_d_array(char **array)
{
	size_t	i;

	i = -1;
	while (array[++i])
		printf(">%s<\n", array[i]);
}
