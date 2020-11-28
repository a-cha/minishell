/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:00:10 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/13 14:03:36 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sign '-' include ONLY in the first function
*/

int		ft_numlen(int n, int base)
{
	int i;

	i = 1;
	if (n < 0)
		n++;
	while (n /= base)
		i++;
	return (i);
}

size_t	ft_numlen_base(long long n, int base)
{
	size_t i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

size_t	ft_numlen_uns(unsigned long long n, int base)
{
	size_t i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}
