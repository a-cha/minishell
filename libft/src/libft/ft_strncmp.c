/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 02:21:49 by sadolph           #+#    #+#             */
/*   Updated: 2020/05/12 00:20:42 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (0 == n)
		return (0);
	if (*s1 && *s2)
	{
		while (--n && s1[i])
		{
			if (s1[i] != s2[i])
				break ;
			i++;
		}
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
