/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 02:05:19 by sadolph           #+#    #+#             */
/*   Updated: 2020/05/09 12:47:32 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;

	if (!(*needle))
		return ((char *)haystack);
	if (len && *haystack)
	{
		i = ft_strlen(needle);
		while (*haystack && i <= len--)
			if (!(ft_strncmp(haystack++, needle, i)))
				return ((char *)--haystack);
	}
	return (NULL);
}
