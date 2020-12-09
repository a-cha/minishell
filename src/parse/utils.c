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

void		free_memory(void *memory)
{
	free(memory);
	memory = NULL;
}

int			free_and_exit(char *s1, char *s2, t_data *part, char flag)
{
	if (s1)
		free_memory(s1);
	if (s2)
		free_memory(s2);
	if (flag == 1)
		ft_exit(part, EXIT_FAILURE);
	return (1);
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
