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
//
	char				*str;
	char				*tmp;

//	i = 1;
//	flag = 0;
//	if (ft_strcmp(data->args[i], "-n") == 0)
//		i++ && flag++;
//	if (data->len > 1)
//	{
//		while (data->args[i])
//		{
//			if (i == data->len)
//			{
//				ft_putstr_fd(data->args[i], 1);
//				break ;
//			}
//			ft_putstr_fd(data->args[i], 1);
//			ft_putstr_fd(" ", 1);
//			i++;
//		}
//	}
//	if (flag == 0)
//		ft_putstr_fd("\n", 1);

	i = 0;
	flag = 0;
	str = NULL;
	tmp = NULL;
	if (data->args[1])
		if (!(ft_strcmp(data->args[1], "-n")))
			i++ && flag++;
	while (data->args[++i])
	{
		str = data->args[i];
		if (!(is_first_symbol(data->args[i], '$')))
		{
			tmp = ft_substr(data->args[i], 1, ft_strlen(data->args[i]));
			str = find_env(&data->env, tmp);
			free(tmp);
		}
		if (i == (data->len) - 1)
		{
			ft_putstr_fd(str, 1);
			break;
		}
		ft_putstr_fd(str, 1);
		ft_putstr_fd(" ", 1);
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
}
