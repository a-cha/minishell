/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:31:16 by sadolph           #+#    #+#             */
/*   Updated: 2020/05/11 22:49:45 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n-- && (dst || src))
	{
		*((unsigned char*)dst) = *((unsigned char*)src++);
		if (*(unsigned char*)(dst++) == (unsigned char)c)
			return (dst);
	}
	return (NULL);
}
