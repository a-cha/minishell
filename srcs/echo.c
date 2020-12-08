/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:49:23 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/21 21:36:19 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data)
{
	unsigned long int	i;
	int					flag;
	char				*str;

	i = 0;
	flag = 0;
	str = NULL;
	if (data->args)
	{
		if (data->args[1])
			if (!(ft_strcmp(data->args[1], "-n")))
			{
				i++;
				flag++;
			}
		while (data->args[++i])
		{
			str = data->args[i];
			if (i == (data->len) - 1)
			{
				ft_putstr_fd(str, 1);
				break ;
			}
			ft_putstr_fd(str, 1);
			if (data->args[i + 1])
				ft_putstr_fd(" ", 1);
		}
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	last_status = 0;
}
