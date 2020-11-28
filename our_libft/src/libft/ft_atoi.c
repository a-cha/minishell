/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:26:52 by sadolph           #+#    #+#             */
/*   Updated: 2020/05/11 22:54:18 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char *str)
{
	int				i;
	int				s;
	unsigned int	prev;
	int				res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	s = i - 1;
	while (ft_isdigit(str[i]))
	{
		prev = (unsigned int)res;
		res = res * 10 + (str[i++] - '0');
		if (i - s > 20 && prev > (unsigned int)res)
			return (str[s] == '-' ? 0 : -1);
	}
	if (str[s] == '-')
		res *= -1;
	return (res);
}
