/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:38:39 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/21 22:41:00 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(/*int argc, char **argv*/)
{
	t_data data;
	char	*line;

	// data.len = argc - 1;
	while (1)
	{
		ft_putstr_fd("kekai > ", 1);
		get_next_line(1, &line);
		data.args = ft_split(line, ' ');
		// parsed = parse(line);
		cd(&data);
		pwd(&data);
	}
	// echo(&data);
	return (0);
}
