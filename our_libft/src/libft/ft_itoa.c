/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 20:03:22 by sadolph           #+#    #+#             */
/*   Updated: 2020/05/11 22:44:28 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Counts symbols in number (sign '-' also counts)
*/

char		*ft_itoa(int n)
{
	int		len;
	char	*res;

	len = ft_numlen(n, 10);
	if (!(res = (char *)ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	if (n == 0)
		res[0] = '0';
	else if (n < 0)
		res[0] = '-';
	while (n)
	{
		if (n < 0)
			res[--len] = (n % 10) * -1 + '0';
		else
			res[--len] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
