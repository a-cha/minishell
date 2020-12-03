/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:44:29 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/28 16:44:40 by sadolph          ###   ########.fr       */
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
** Reset struct to the next round of parsing & processing
*/

void			reset_t_data(t_data *data)
{
	ft_arrayfree(data->args);
	data->args = (char **)ft_calloc(1, sizeof(char **));
	*(data->args) = NULL;
	data->len = -1;
//	why this strings commented?
	if (data->infile >= 0)
	{
		close(data->infile);
		data->infile = -1;
	}
	if (data->outfile >= 0)
	{
		close(data->outfile);
		data->outfile = -1;
	}
//	what is this?
//	if (data->infile == -1)
//		data->infile = 0;
//	if (data->outfile == -1)
//		data->outfile = 0;
//	close fd after redirections
	if (data->type != '|')
	{
		dup2(data->orig_input, 0);
		dup2(data->orig_output, 1);
	}
}
