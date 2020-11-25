/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:38:39 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/23 20:56:10 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_data  *data;
	char	*line;
	data = malloc(sizeof (t_data));

	data->env = dup_env(env);
//	test_env_list(&data->env);

	while (1)
	{
		ft_putstr_fd("minishell > ", 1);
		get_next_line(1, &line);
//		line = "echo -n kak $PWD $PATH";
		data->args = ft_split(line, ' ');
		data->len = ft_arraylen((char**)data->args);
		if (ft_strcmp(data->args[0], "cd") == 0)
            cd(data);
		else if (ft_strcmp(data->args[0], "pwd") == 0)
            pwd(data);
		else if (ft_strcmp(data->args[0], "echo") == 0)
		    echo(data);
		else if (!(ft_strcmp(data->args[0], "env")))
			test_env_list(&data->env);
		else if (!(ft_strcmp(data->args[0], "exit")))
			ft_exit(data);
		else if (!(ft_strcmp(data->args[0], "export")))
		{
			if (is_first_symbol(data->args[1], '$') == 0)
					env_export(data);
			else
				env_export(data);
		}
		else if (data->args[0])
			extern_bin(data, env);
		int i = -1;
		while (data->args[++i])
			free(data->args[i]);
//         parsed = parse(line);
	}
	return (0);
}

