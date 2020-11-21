/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:49:23 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/21 19:43:22 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data)
{
	unsigned long int	i;
	int					flag;

	i = 1;
	flag = 0;
	if (ft_strcmp(data->args[i], "-n") == 0)
		i++ && flag++;
	if (data->len != 0)
	{
		while (data->args[i])
		{
			if (i == data->len)
			{
				ft_putstr_fd(data->args[i], 1);
				break ;
			}
			ft_putstr_fd(data->args[i], 1);
			ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
}
