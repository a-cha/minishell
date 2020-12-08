/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <pcatrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:19:22 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/23 21:33:52 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		*free_and_exit_1(char **array, char *str)
{
	if (array)
		ft_arrayfree(array);
	if (str)
		free_memory(str);
	return (NULL);
}

char			**list_to_array(t_data *data)
{
	char		**env;
	int			i;
	char		*tmp;
	t_list		*lst;
	t_env		*current;

	if (!(env = (char **)malloc(sizeof(char *) * (ft_lstsize(data->env) + 1))))
		return (NULL);
	i = -1;
	lst = data->env;
	while (lst)
	{
		current = lst->content;
		if (!(tmp = ft_strjoin(current->env_name, "=")))
			return (free_and_exit_1(env, NULL));
		if (!(env[++i] = ft_strjoin(tmp, current->env_cont)))
			return (free_and_exit_1(env, tmp));
		free_memory(tmp);
		lst = lst->next;
	}
	env[i + 1] = NULL;
	return (env);
}

char			*is_corr_path(char **arr, char *str)
{
	struct stat	stats;
	char		*buff;
	char		*buff1;
	int			i;

	i = -1;
	while (arr[++i])
	{
		if (!(buff = ft_strjoin(arr[i], "/")))
			return (NULL);
		if (!(buff1 = ft_strjoin(buff, str)))
		{
			free_memory(buff);
			return (NULL);
		}
		free_memory(buff);
		if (stat(buff1, &stats) == 0)
		{
			if (stats.st_mode & X_OK)
				return (buff1);
		}
		free_memory(buff1);
	}
	return (NULL);
}

int				our_command(t_data *data)
{
	if (data->args[0])
	{
		if (!(ft_strcmp(data->args[0], "cd")))
			return (for_return(data, cd));
		else if (!(ft_strcmp(data->args[0], "pwd")))
			return (for_return(data, pwd));
		else if (!(ft_strcmp(data->args[0], "echo")))
			return (for_return(data, echo));
		else if (!(ft_strcmp(data->args[0], "export")))
			return (for_return(data, env_export));
		else if (!(ft_strcmp(data->args[0], "unset")))
			return (for_return(data, env_unset));
		else if (!(ft_strcmp(data->args[0], "env")))
		{
			test_env_list(&data->env);
			return (0);
		}
		else if (!(ft_strcmp(data->args[0], "exit")))
		{
			ft_exit(data, g_last_status);
			return (0);
		}
		return (1);
	}
	return (1);
}
