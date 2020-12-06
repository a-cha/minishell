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

char		**list_to_array(t_data *data)
{
	char		**env;
	int 		i;
	char 		*tmp;
	t_list 		*lst;
	t_env 		*current;

	if (!(env = (char **)malloc(sizeof(char *) * (ft_lstsize(data->env) + 1))))
		return (NULL);
	i = -1;
	lst = data->env;
	while (lst)
	{
		current = lst->content;
		if (!(tmp = ft_strjoin(current->env_name, "=")))
		{
			free_memory(env);
			return (NULL);
		}
		if (!(env[++i] = ft_strjoin(tmp, current->env_cont)))
		{
			free_memory(env);
			free_memory(tmp);
			return (NULL);
		}
		free_memory(tmp);
		lst = lst->next;
	}
	env[i + 1] = NULL;
	return (env);
}

void			extern_bin(t_data *data)
{
	char		**ar;
	char		*str;
	int 		child;
	char 		**env;
	char		*check;
//	int			fd_in;
//	int 		fd_out;

	check = find_env(&data->env, "PATH");
	if (data->args[0][0] != '/' && check != NULL)
	{
		if (!(ar = ft_split(check, ':')))
			ft_exit(data, EXIT_FAILURE);
//		if (!(ar = ft_split(find_env(&data->env, "PATH"), ':')))
//			ft_exit(data, EXIT_FAILURE);
		if ((str = is_corr_path(ar, data->args[0])) == NULL)
			if (!(str = ft_strdup(data->args[0])))
			{
				ft_arrayfree(ar);
				ft_exit(data, EXIT_FAILURE);
			}
	}
	else
		if (!(str = ft_strdup(data->args[0])))
			ft_exit(data, EXIT_FAILURE);
	if (!(env = list_to_array(data)))
	{
		free_memory(str);
		ft_arrayfree(ar);
		ft_exit(data, EXIT_FAILURE);
	}
//	fd_in = install_in_fd(data);
//	fd_out = install_out_fd(data);
//	dup2(fd_in, 0);
//	close(fd_in);
//	dup2(fd_out, 1);
//	close(fd_out);
	child = fork();
	if (child == -1)
		ft_exit(data, EXIT_FAILURE);
	else if (child == 0)
	{
		execve((const char *) str, data->args, env);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_memory(str);
		if (data->args[0][0] != '/' && check != NULL)
			ft_arrayfree(ar);
		ft_arrayfree(env);
		last_status = 127;
		exit(127);
	}
	else
	{
		parent_process(data, child);
//		waitpid(child ,&status, 0);
//		if (WIFEXITED(status))
//			last_status = WEXITSTATUS(status);
	}
	if (data->args[0][0] != '/' && check != NULL)
		ft_arrayfree(ar);
	free_memory(str);
	ft_arrayfree(env);
//	ft_exit(data, 127);
}

char			*is_corr_path(char **arr, char *str)
{
	struct stat	stats;
	char		*buff;
	char		*buff1;
	int 		i;

	i= -1;
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
//			printf("File access: ");
//			if (stats.st_mode & R_OK)
//				printf("read ");
//			if (stats.st_mode & W_OK)
//				printf("write ");
			if (stats.st_mode & X_OK)
				return (buff1);
//				printf("execute\n");
//			printf("\nFile size: %lld", stats.st_size);

		}
		free_memory(buff1);
	}
	return (NULL);
}
