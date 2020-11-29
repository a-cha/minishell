/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:45:39 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/23 17:15:04 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	renew_pwd(t_list *env_dup, char *cd)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = find_env1(&env_dup, "PWD");
	oldpwd = find_env1(&env_dup, "OLDPWD");
	free_memory(oldpwd->env_cont);
	oldpwd->env_cont = pwd->env_cont;
	pwd->env_cont = cd;
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
	}
	else if (!(ft_strcmp(data->args[1], "-")))
	{
		tmp = find_env(&data->env, "OLDPWD");
		chdir(tmp);
		pwd(data);
	}
	else if (chdir(data->args[1]) == -1)
	{
		last_status = 1;
		return (ft_putstr_fd("cd: No such file or directory \n", 1));
	}
	last_status = 0;
	cd = getcwd(NULL, 0);
	renew_pwd(data->env, cd);
	free(cd);
}
