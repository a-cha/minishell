/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:50:34 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/13 17:06:57 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	renew_params(char *buf, char **line)
{
	char	*endline;

	if (!(endline = ft_strchr(buf, '\n')))
	{
		if (!(*line = ft_strjoin_pro(line, buf)))
			return (1);
	}
	else
	{
		*endline = '\0';
		if (!(*line = ft_strjoin_pro(line, buf)))
			return (-1);
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	size_t		rd;
	char		*buf;
	int			rp;

	if (BUFFER_SIZE < 1 || fd < 0 || !line ||
						!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	*line = malloc(1);
	**line = '\0';
	while ((rd = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[rd] = '\0';
		if ((rp = renew_params(buf, line)))
			return (free_buf(&buf, rp));
		if (rd == 0 && !**line)
			return (free_buf(&buf, rd));
	}
	return (free_buf(&buf, rd));
}
