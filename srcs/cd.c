/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:45:39 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/22 20:53:04 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_data *data)
{
	char	*cd;
	char	*tmp;

	if (!(data->args[1]))
    {
		tmp = find_env(data->env, "HOME");
		chdir(tmp);
		free(tmp);
		return;
	}
	if (chdir(data->args[1]) == -1)
		return (ft_putstr_fd("cd: No such file or directory \n", 1));
	cd = getcwd(NULL, 0);
//	data->pwd = cd;
	free(cd);
}