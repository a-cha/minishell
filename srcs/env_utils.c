/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <pcatrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:05:08 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/22 21:07:20 by pcatrina         ###   ########.fr       */
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

char 	**dub_env(char **env)
{
	char	**env_dup;
	int		i;

	i = 0;

	env_dup = (char **)malloc(8 * (ft_arraylen((void**)env) + 1));
	while (env[i])
	{
		env_dup[i] = ft_strdup(env[i]);
		i++;
	}
	return (env_dup);
}