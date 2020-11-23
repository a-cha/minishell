/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:45:39 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/23 13:42:16 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	renew_pwd(t_data *data, char *cd)
{
	t_list 	*tmp;
	t_env	*env;

	tmp = data->env;
	find_env()
}

void	cd(t_data *data)
{
	char	*cd;
	char	*tmp;

	if (!(data->args[1]) || !(ft_strcmp((const char *)data->args[1], "~")) ||
			!(ft_strcmp((const char *)data->args[1], "--")))
	{
		tmp = find_env(&data->env, "HOME");
		chdir(tmp);
		free(tmp);
		return ;
	}
	else if (chdir(data->args[1]) == -1)
		return (ft_putstr_fd("cd: No such file or directory \n", 1));
	cd = getcwd(NULL, 0);
	free(cd);
	renew_pwd(data, cd);
}
