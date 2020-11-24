/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 23:11:16 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/24 23:11:18 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*find_prev(t_list **env_dup, char *str)
{
	t_list		*tmp;
	t_list		*prev;
	t_env		*env;

	tmp = *env_dup;
	prev = tmp;
	while (tmp)
	{
		env = tmp->content;
		if (!(ft_strcmp((const char *)env->env_name, str)))
			return (prev);
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

void 		remove_elem(t_list **env_dup, char *str)
{
	t_list		*prev;
	t_list		*tmp;

	prev = find_prev(env_dup, str);
	if (!(prev->next))
	{
		(*env_dup)->next = NULL;
		free_memory(prev);
	}
	else
	{
		tmp = prev->next;
		prev->next = tmp->next;
		free_memory(tmp);
	}
}
