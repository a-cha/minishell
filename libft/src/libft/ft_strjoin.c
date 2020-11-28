/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 20:03:22 by sadolph           #+#    #+#             */
/*   Updated: 2020/05/12 00:20:25 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	if (!s1)
		s1 = "\0";
	if (!s2)
		s2 = "\0";
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if ((res = (char *)malloc((len1 + len2 + 1) * sizeof(char))))
	{
		ft_strlcpy(res, s1, len1 + 1);
		ft_strlcat(res, s2, len1 + len2 + 1);
	}
	return (res);
}
