/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:41:56 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 22:12:17 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Duplicate & sort list. Returns a new sorted list.
*/
t_list		*list_dup_sort(const t_data *data)
{
	t_list	*tmp;
	t_list	*start;
	t_env	*cur_env;
	t_env	*next_env;
	t_env	*tmp_name;

	start = ft_lstmap(data->env, copy_t_env, del_content);
	tmp = start;
	while(tmp->next)
	{
		cur_env = tmp->content;
		next_env = tmp->next->content;
		if ((ft_strcmp(cur_env->env_name, next_env->env_name)) > 0)
		{
			tmp_name = tmp->next->content;
			tmp->next->content = tmp->content;
			tmp->content = tmp_name;
			tmp = start;
			continue ;
		}
		tmp = tmp->next;
	}
	return (start);
}

char		*find_env(t_list **env_dup, char *str)
{
	t_list	*tmp;
	t_env	*env;

	tmp = *env_dup;
	while (tmp)
	{
		env = tmp->content;
		if (!(ft_strcmp((const char *)env->env_name, str)))
			return (env->env_cont);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env		*find_env1(t_list **env_dup, char *str)
{
	t_list	*tmp;
	t_env	*env;

	tmp = *env_dup;
	while (tmp)
	{
		env = tmp->content;
		if (!(ft_strcmp((const char *)env->env_name, str)))
			return (env);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list		*find_env2(t_list **env_dup, char *str)
{
	t_list	*tmp;
	t_env	*env;

	tmp = *env_dup;
	while (tmp)
	{
		env = tmp->content;
		if (!(ft_strcmp((const char *)env->env_name, str)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env		*env_to_cont(char *env)
{
	t_env	*var;
	char 	*tmp;

	var = (t_env *)malloc(sizeof(t_env));
	tmp = ft_strchr(env, '=');
	var->env_name = ft_substr(env, 0, tmp - env);
	var->env_cont = ft_substr(env, tmp - env + 1, ft_strlen(env));
	if ((tmp) != NULL)
		var->is_equal = 1;
	else
		var->is_equal = 0;
	return (var);
}

t_list		*dup_env(char **env)
{
	t_list	*env_dup;
	int		i;

	i = -1;
	env_dup = NULL;
	while (env[++i])
		ft_lstadd_back(&env_dup, ft_lstnew(env_to_cont(env[i])));
	return (env_dup);
}

void		test_env_list(t_list **env_dup)
{
	t_list *tmp;
	t_env  *env;
	tmp = *env_dup;
	while (tmp)
	{
		env = tmp->content;
		if (env->is_equal == 1)
		{
			ft_putstr_fd((env->env_name), 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd((env->env_cont), 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}

