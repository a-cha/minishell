/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:38:39 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/22 15:12:35 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_data data;
	char	*line;
	char	**env_dup;
	int		i;

	env_dup = malloc(8 * (array_len(env) + 1));
	while (env)
	{
		env_dup[i] = ft_strdup(env[i]);
		i++;
	}
	data.env = env_dup;
	// data.len = argc - 1;
	while (1)
	{
		ft_putstr_fd("minishell > ", 1);
		get_next_line(1, &line);
		data.args = ft_split(line, ' ');
		// parsed = parse(line);
		// pwd(&data);
		cd(&data);
	}
	// echo(&data);
	return (0);
}
