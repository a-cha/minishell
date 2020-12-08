/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:20:29 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/29 22:20:31 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			for_return(t_data *data, void (*f)(t_data *data))
{
	f(data);
	return (0);
}

int					our_command_if_no_pipe(t_data *data)
{
	if (data->args[0] && data->type != '|')
	{
		if (!(ft_strcmp(data->args[0], "cd")))
			return (for_return(data, cd));
		else if (!(ft_strcmp(data->args[0], "export")))
			return (for_return(data, env_export));
		else if (!(ft_strcmp(data->args[0], "unset")))
			return (for_return(data, env_unset));
		else if (!(ft_strcmp(data->args[0], "exit")))
		{
			ft_exit(data, last_status);
			return (0);
		}
		return (1);
	}
	return (1);
}

static char			*corr_path(t_data *data)
{
	char *check;
	char **ar;
	char *str;

	check = find_env(&data->env, "PATH");
	if (data->args[0][0] != '/' && check != NULL)
	{
		if (!(ar = ft_split(check, ':')))
			ft_exit(data, EXIT_FAILURE);
		if ((str = is_corr_path(ar, data->args[0])) == NULL)
			if (!(str = ft_strdup(data->args[0])))
			{
				ft_arrayfree(ar);
				ft_exit(data, EXIT_FAILURE);
			}
		ft_arrayfree(ar);
	}
	else if (!(str = ft_strdup(data->args[0])))
		ft_exit(data, EXIT_FAILURE);
	return (str);
}

void				child_process(t_data *data)
{
	char		**ar;
	char		*str;
	char		**env;

	last_status = 0;
	errno = 0;
	if (data->pipe_fd[0])
		close(data->pipe_fd[0]);
	if (our_command(data) == 0)
		exit(EXIT_SUCCESS);
	str = corr_path(data);
	if (!(env = list_to_array(data)))
	{
		free_memory(str);
		ft_exit(data, EXIT_FAILURE);
	}
	execve((const char *)str, data->args, env);
	if (errno == 13)
	{
		free_memory(str);
		ft_arrayfree(env);
		exit(126);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_memory(str);
	ft_arrayfree(env);
	last_status = 127;
	exit(127);
}
