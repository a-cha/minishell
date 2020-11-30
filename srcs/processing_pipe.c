/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:20:29 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/29 22:20:31 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				parent_process(t_data *data, int pid)
{
	int status;

	status = 0;
	dup2(data->orig_input, 0);
	dup2(data->orig_input, 1);
	last_pid = pid;
	while (status != -1)
		status = process_status();
}

void				child_process(t_data *data)
{
	last_status = 0;
	if (data->pipe_fd[0])
		close(data->pipe_fd[0]);
	processing(data);
}


static int			install_out_fd(t_data *data)
{
	int fd_out;

	fd_out = 0;
	if (data->type)
	{
		if (pipe(data->pipe_fd) == -1)
			ft_exit(data, -1);
		fd_out = dup(data->pipe_fd[1]);
	}
	return (fd_out);
}

static int 			install_in_fd(t_data *data)
{
	int fd_in;

	fd_in = 0;
	if (data->orig_input)
		fd_in = data->orig_input;
	else if (data->pipe_fd[0])
		fd_in = dup(data->pipe_fd[0]);
	if (data->pipe_fd[0])
		close(data->pipe_fd[0]);
	data->pipe_fd[0] = 0;
	return (fd_in);
}

void				processing_pipe(t_data *data)
{
	int fd_in;
	int fd_out;
	int pid;

	fd_in = install_in_fd(data);
	fd_out = install_out_fd(data);
	printf("fd_in: %d, fd_out: %d\n", fd_in, fd_out);
	pid = fork();
	if (pid == -1)
	{
		ft_exit(data, -1);
	}
	else if (pid  == 0)
		child_process(data);
	if (!data->type)
		parent_process(data, pid);
}
