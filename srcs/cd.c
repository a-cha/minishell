/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:45:39 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/22 14:55:36 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_data *data)
{
	char	*cd;

	if (!(data->args[1]))
	{
		chdir("");
		return;
	}
	if (chdir(data->args[1]) == -1)
		return (ft_putstr_fd("error", 1));
	cd = getcwd(NULL, 0);
	data->pwd = cd;
	free(cd);
}
