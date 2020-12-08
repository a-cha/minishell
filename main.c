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
		print_error(argv[0], "The program must not have arguments", 1);
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
	*(data->args) = NULL;
	data->orig_input = dup(0);
	data->orig_output = dup(1);
	data->infile = -1;
	data->outfile = -1;
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

int 		read_stdin(t_data *data, char **line)
{
	int		gnl;

	while ((gnl = get_next_line(0, line)) == 0)
	{
		if (!**line)
		{
			last_status = 131;
			ft_exit(data, last_status);
		}
		free_memory(*line);
	}
	return (gnl);
}

static void		execution(t_data *data)
{
	int		in_fd;
	int 	out_fd;
	pid_t	pid;

	if (our_command_if_no_pipe(data) != 1)
		return ;
	in_fd = install_in_fd(data);
	out_fd = install_out_fd(data);
	dup2(in_fd, 0);
	close(in_fd);
	dup2(out_fd, 1);
	close(out_fd);
	pid = fork();
	if (pid == -1)
		ft_exit(data, EXIT_FAILURE);
	else if (pid == 0)
	{
//		dup2(data->pipe_fd[1], 1);
//		close(data->pipe_fd[0]);
		child_process(data);
//		close(data->pipe_fd[1]);
	}
	else
	{
//		dup2(data->pipe_fd[0], 0);
//		close(data->pipe_fd[1]);
		parent_process(data, pid);
//		close(data->pipe_fd[0]);
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
		ft_putstr_fd("minihell > ", 1);
		errno = 0;
		sigint_flag = 0;
		n = 0;
		if ((read_stdin(data, &line)) == -1)
			ft_exit(data, EXIT_FAILURE);
		while (*(line + n))
		{
			if ((n += parse(line + n, data)) < 0)
			{
				free_memory(line);
				ft_exit(data, EXIT_FAILURE);
			}
			execution(data);
//			if (data->type == '|')
//				new_processing(data);
////			print_d_array(data->args);
////			if (data->type == '|')
////				processing_pipe(data);
//			else
//				processing(data);
			if (*(line + n))
				reset_t_data(data);
		}
		reset_t_data(data);
		free_memory(line);
//		tmp = dup(0);
//		printf("%d\n", tmp);
//		close(tmp);
	}
}
