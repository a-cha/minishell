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
		print_error(argv[0], "You must not have arguments", 1);
		exit(EXIT_FAILURE);
	}
	if (!(data = ft_calloc(1, sizeof(t_data))))
		exit(EXIT_FAILURE);
	if (!(data->env = dup_env(env)))
	{
		free_memory(data);
		exit(EXIT_FAILURE);
	}
	if (!(data->args = (char **)ft_calloc(1, sizeof(char *))))
	{
		free_memory(data);
		ft_lstclear(&data->env, del_content);
		exit(EXIT_FAILURE);
	}
	signal_oper();
	return (data);
}

void	processing(t_data *data)
{
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
			extern_bin(data);
//		int i = -1;
//		while (data->args[++i])
//			free_memory(data->args[i]);
//         parsed = parse(line);
	}

}

int			main(int argc, char **argv, char **env)
{
	t_data  *data;
	char	*line;
	int 	n;

	data = shell_init(argc, argv, env);
	while (1)
	{
		ft_putstr_fd("Вводи > ", 1);
		if ((get_next_line(0, &line)) == -1)
			ft_exit(data, last_status);
		errno = 0;
		sigint_flag = 0;
		reset_t_data(data);
		while (*line)
		{
			if ((n = parse(line, data)) < 0)
			{
				free_memory(line);
				ft_exit(data, EXIT_FAILURE);
			}
			processing(data);
			line += n;
		}
	}
	return (0);
}
