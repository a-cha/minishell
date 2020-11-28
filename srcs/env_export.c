/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:39:48 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/24 11:39:50 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_new_env(t_data *data)
{
	t_list	*tmp;
	int 	i;

	i = 0;
	tmp = data->env;
	while (data->args[++i])
		ft_lstadd_back(&tmp, ft_lstnew(env_to_cont(data->args[i])));
	ft_lstdelone(tmp, del_content);
}

void	rewrite_cont(t_data *data, t_env *env)
{
	int		i;
	char 	*tmp;
	char	*name;
	char 	*cont;

	i = 0;
	while (data->args[++i])
	{
		tmp = ft_strchr(data->args[i], '=');
		name = ft_substr(data->args[i], 0, tmp - data->args[i]);
		cont = ft_substr(data->args[i], tmp - data->args[i] + 1, ft_strlen
		(data->args[i]));
		if (!ft_strcmp(env->env_name, name))
		{
			free_memory(env->env_cont);
			env->env_cont = (char *) malloc(sizeof(char) * (ft_strlen(cont) +
					1));
			env->env_cont = cont;
		}
		free_memory(name);
	}
}

void       print_exp_list(t_list **env_dup, t_data *data)
{
	t_list *tmp;
	t_env  *env;

	tmp = *env_dup;

		while (tmp)
		{
			env = tmp->content;
			if (is_first_symbol(env->env_name, '_') == -1)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd((env->env_name), 1);
				if (env->is_equal == 1 && *(env->env_cont) == '\0')
					ft_putstr_fd("=\"\"", 1);
				if (*(env->env_cont) != '\0')
				{
					ft_putstr_fd("=\"", 1);
					ft_putstr_fd((env->env_cont), 1);
					ft_putstr_fd("\"", 1);
				}
				ft_putstr_fd("\n", 1);
			}
			tmp = tmp->next;
		}
}

void		env_export(t_data *data)
{
	t_list	*new_list;
	t_env 	*env;

	if (data->args[1])
	{
		env = chek_env(data);
		if (env == NULL)
			set_new_env(data);
		else
			rewrite_cont(data, env);
		new_list = list_dup_sort(&data->env);
		return ;
	}
	new_list = list_dup_sort(&data->env);
	print_exp_list(&new_list, data);
	ft_lstclear(&new_list, del_content);
}

int		is_first_symbol(const char *str, char c)
{
	if (!str)
		return (-1);
	else if (str[0] == c)
		return (0);
	return (-1);
}

t_env 	*chek_env(t_data *data)
{
	t_list	*list;
	t_env 	*env;
	char	*str;
	char 	*tmp;
	int 	i;

	i = 0;
	while (data->args[++i])
	{
		str = ft_strchr(data->args[i], '=');
		if (!(tmp = ft_substr(data->args[i], 0, str - data->args[i])))
			ft_exit(data, EXIT_FAILURE);
		list = data->env;
		while (list)
		{
			env = find_env1(&list, tmp);
			if (env != NULL)
				return (env);
			list = list->next;
		}
		free(tmp);
	}
	return (NULL);
}


