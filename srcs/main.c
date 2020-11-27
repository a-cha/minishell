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

int		last_status = 0;
int		last_pid = 0;
int		sigint_flag = 0;

t_data	*shell_init(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc != 1)
	{
		print_error(argv[0], "You must have arguments", 1);
		exit(EXIT_FAILURE);
	}
	if (!(data = malloc_shell(env)))
		ft_exit(data, EXIT_FAILURE);
	signal_oper();
	return (data);
}

int		main(int argc, char **argv, char **env)
{
	t_data  *data;
	char	*line;

	data = shell_init(argc, argv, env);
	data->env = dup_env(env);
//	while (1)
//	{
		ft_putstr_fd("minishell: ", 1);
//		if (get_next_line(1, &line) == -1)
//			ft_exit(data, last_status);
//		errno = 0;
		line = "unset govno";
		sigint_flag = 0;
		data->args = ft_split(line, ' ');
		data->len = ft_arraylen((char**)data->args);
		if(data->args[0])
		{
			if (ft_strcmp(data->args[0], "cd") == 0)
				cd(data);
			else if (ft_strcmp(data->args[0], "pwd") == 0)
				pwd(data);
			else if (ft_strcmp(data->args[0], "echo") == 0)
				echo(data);
			else if (!(ft_strcmp(data->args[0], "env")))
				test_env_list(&data->env);
			else if (!(ft_strcmp(data->args[0], "exit")))
				ft_exit(data, last_status);
			else if (!(ft_strcmp(data->args[0], "export")))
				env_export(data);
			else if (!(ft_strcmp(data->args[0], "unset")))
				env_unset(data);
			else if (data->args[0])
				extern_bin(data, env);
			int i = -1;
			while (data->args[++i])
				free_memory(data->args[i]);
//         parsed = parse(line);
//		}
	}
	return (0);
}

