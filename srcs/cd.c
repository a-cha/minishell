/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:45:39 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/23 17:13:12 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	renew_pwd(t_list *env_dup, char *cd)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = find_env1(&env_dup, "PWD");
	oldpwd = find_env1(&env_dup, "OLDPWD");
//	free(oldpwd->env_cont); Узанть что не так с утечками <- ТУТ
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
		cd = getcwd(NULL, 0);
		renew_pwd(data->env, cd);
		free(cd);
		return ;
	}
	else if (!(ft_strcmp(data->args[1], "-")))
	{
		tmp = find_env(&data->env, "OLDPWD");
		chdir(tmp);
		pwd(data);
		cd = getcwd(NULL, 0);
		renew_pwd(data->env, cd);
		free(cd);
		return ;
	}
	else if (chdir(data->args[1]) == -1)
		return (ft_putstr_fd("cd: No such file or directory \n", 1));
	cd = getcwd(NULL, 0);
	renew_pwd(data->env, cd);
	free(cd);
}
