/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <pcatrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:05:08 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/22 23:39:21 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*find_env(char **env, char *str)
{
	int 	i;
	char	*arr;

	i = 0;
	arr = 0;
	while (env[i])
	{
		if ((ft_strncmp((const char *)env[i], str, ft_strlen(str)) == 0))
		{
			arr = ft_substr((const char *)env[i], ft_strlen(str) + 1,
				   ft_strlen((const char *)env[i]));
			break;
		}
		i++;
	}
	return (arr);
}

t_env	*env_to_cont(char *env)
{
	t_env	*var;
	char 	*tmp;

//	PATH=/kek/lol
//	PATH2=/kek/lol
	var = (t_env *)malloc(sizeof(t_env));
	tmp = ft_strchr(env, '=');
	var->env_name = ft_substr(env, 0, tmp - env);
	var->env_cont = ft_substr(env, tmp - env + 1, ft_strlen(env));
	return (var);
}

t_list	*dub_env(char **env)
{
	t_list	*env_dup;
	int		i;

	i = -1;
	env_dup = NULL;
	while (env[++i])
		ft_lstadd_back(&env_dup, ft_lstnew(env_to_cont(env[i])));
	return (env_dup);
}
