/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:57:05 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 13:57:05 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_content(void *elem)
{
	t_env *env;

	env = elem;
	free_memory(env->env_name);
	free_memory(env->env_cont);
	free(elem);
	elem = NULL;
}

void	*copy_t_env(void *elem)
{
	t_env *env;
	t_env *el_env;

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
