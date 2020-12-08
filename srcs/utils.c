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
** Frees pointer's content and turns it to NULL
*/
void		free_memory(void *memory)
{
	free(memory);
	memory = NULL;
}

/*
** Reset struct to the next round of parsing & processing
*/

void		reset_t_data(t_data *data)
{
	ft_arrayfree(data->args);
	data->args = (char **)ft_calloc(1, sizeof(char **));
	*(data->args) = NULL;
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
	data->flag_redir = 0;
//	what is this?
//	if (data->infile == -1)
//		data->infile = 0;
//	if (data->outfile == -1)
//		data->outfile = 0;
//	close fd after redirections
//	if (data->type != '|')
//	{
		dup2(data->orig_input, 0);
		dup2(data->orig_output, 1);
//	}
}

/*
** Returns max value
*/

int			max(int n1, int n2)
{
	return (n1 > n2 ? n1 : n2);
}

/*
** Functions for correct use of the ft_lstmap
*/

void		del_content(void *elem)
{
	t_env	*env;

	env = elem;
	free_memory(env->env_name);
	free_memory(env->env_cont);
	free_memory(elem);
}

void		*copy_t_env(void *elem)
{
	t_env	*env;
	t_env	*el_env;

	if ((env = (t_env *)malloc(sizeof(t_env))))
	{
		el_env = elem;
		if (!(env->env_name = ft_strdup(el_env->env_name)))
		{
			free_memory(env);
			return (NULL);
		}
		if (!(env->env_cont = ft_strdup(el_env->env_cont)))
		{
			free_memory(env);
			free_memory(env->env_name);
			return (NULL);
		}
		env->is_equal = el_env->is_equal;
	}
	return (env);
}
