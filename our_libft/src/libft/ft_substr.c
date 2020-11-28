/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 20:03:22 by sadolph           #+#    #+#             */
/*   Updated: 2020/05/12 15:13:21 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		l;
	char		*res;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	l = ft_strlen(s + start);
	l = l >= len ? len : l;
	if ((res = (char *)malloc((l + 1) * sizeof(char))))
		ft_strlcpy(res, s + start, l + 1);
	return (res);
}
