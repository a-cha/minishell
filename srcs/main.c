/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:38:39 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/23 13:09:33 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_data  *data;
	char	*line;
	data = malloc(sizeof (t_data));

	data->env = dub_env(env);
	test_env_list(&data->env);

	while (1)
	{
		ft_putstr_fd("minishell > ", 1);
		get_next_line(1, &line);
		data->args = ft_split(line, ' ');
		data->len = ft_arraylen((void**)data->args);
		if (ft_strcmp(data->args[0], "cd") == 0)
            cd(data);
		else if (ft_strcmp(data->args[0], "pwd") == 0)
            pwd(data);
		else if (ft_strcmp(data->args[0], "echo") == 0)
		    echo(data);
        // parsed = parse(line);
	}
	return (0);
}
