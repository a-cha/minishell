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

int			is_linebreak(const char *line)
{
	size_t	res;
	size_t	s;

	res = ft_strlen(line);
	if ((s = is_symb(line, SEMICOLON)) < res)
		res = s;
	if ((s = is_symb(line, PIPE)) < res)
		res = s;
	return (res == ft_strlen(line) ? -1 : (int)res);
}

int			is_quotmark(const char *line)
{
	size_t	res;
	size_t	s;

	res = ft_strlen(line);
	if ((s = is_symb(line, '"')) < res)
		res = s;
	if ((s = is_symb(line, '\'')) < res)
		res = s;
	return (res == ft_strlen(line) ? -1 : (int)res);
}

/*
** Returns pointer to first sign (pipe / semicolon / quotation marks)
*/

size_t		catch_first_sign(const char *str, t_data *part, char *r)
{
	size_t	min;
	int		res;

	min = ft_strlen(str);
	if ((res = is_linebreak(str)) != -1 && res < min)
		min = res;
	if ((res = is_quotmark(str)) != -1 && res < min)
		min = res;
	if (str[min] == SEMICOLON)
		part->type = SEMICOLON;
	else if (str[min] == PIPE)
		part->type = PIPE;
	else
		part->type = '\0';
	if (str[min] == '\'' || str[min] == '"')
		*r = str[min];
	else
		*r = '\0';
	return (min);
}

/*
** Reset struct to the next round of parsing
*/

void			reset_t_data(t_data *data)
{
	if (data->args)
		ft_arrayfree(data->args);
	data->args = (char **)ft_calloc(1, sizeof(char **));
	*(data->args) = NULL;
	data->len = -1;
//	why this strings commented?
//	if (data->infile >= 0)
//	{
//		close(data->infile);
//		data->infile = -1;
//	}
//	if (data->outfile >= 0)
//	{
//		close(data->outfile);
//		data->outfile = -1;
//	}
	if (data->infile == -1)
		data->infile = 0;
	if (data->outfile == -1)
		data->outfile = 0;
	dup2(data->orig_input, 0);
	dup2(data->orig_output, 1);
}

//	remove
void	print_d_array(char **array)
{
	size_t	i;

	i = -1;
	while (array[++i])
		printf(">%s<\n", array[i]);
}
