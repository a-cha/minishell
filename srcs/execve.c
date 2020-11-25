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

void	extern_bin(t_data *data, char **env)
{
	char	**ar;
	char	*str;
	int 	child;

	ar = ft_split(find_env(&data->env, "PATH"), ':');
	str = is_corr_path(ar, data->args[0]);
	if ((child = fork()) < 0)
		ft_putstr_fd(": command not found",1);
	else if (child == 0)
	{
		execve((const char *) str, data->args, env);
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(data->args[0], 1);
		ft_putstr_fd(": command not found\n", 1);
	}
	else
		wait(&child);
	free(ar);
}

char	*is_corr_path(char **arr, char *str)
{
	struct stat	stats;
	char		*buff;
	char		*buff1;
	int 		i;

	i= -1;
	while (arr[++i])
	{
		buff = ft_strjoin(arr[i], "/");
		buff1 = ft_strjoin(buff, str);
		free(buff);
		if (stat(buff1, &stats) == 0)
		{
//			printf("File access: ");
//			if (stats.st_mode & R_OK)
//				printf("read ");
//			if (stats.st_mode & W_OK)
//				printf("write ");
//			if (stats.st_mode & X_OK)
//				printf("execute");
//			printf("\nFile size: %lld", stats.st_size);
			return (buff1);
		}
		free(buff1);
	}
	return (0);
}