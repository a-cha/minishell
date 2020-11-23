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
	char	**str;
	char	*arr;
	char	*tmp;
	int		i;
	pid_t	child;

	i = -1;
	str = ft_split(find_env(&data->env, "PATH"), ':');
	while (str[++i])
	{
		tmp = ft_strjoin("/", data->args[0]);
		arr = ft_strjoin(str[i], tmp);
		if ((child = fork()) < 0)
			ft_putstr_fd("error",1);
		else if (child == 0)
			execve((const char *) arr, data->args, env);
		free(arr);
		free(tmp);
	}
	free(str);
}