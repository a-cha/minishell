/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 21:31:44 by pcatrina          #+#    #+#             */
/*   Updated: 2020/12/08 21:31:54 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					reset_t_data(t_data *data)
{
	ft_arrayfree(data->args);
	data->args = (char **)ft_calloc(1, sizeof(char **));
	*(data->args) = NULL;
	if (data->infile >= 0)
	{
		close(data->infile);
		data->infile = -1;
	}
	if (data->outfile >= 0)
	{
		close(data->outfile);
		data->outfile = -1;
	}
	dup2(data->orig_input, 0);
	dup2(data->orig_output, 1);
}

int						install_out_fd(t_data *data)
{
	int fd_out;

	fd_out = 0;
	if (data->type)
	{
		if (pipe(data->pipe_fd) == -1)
			ft_exit(data, EXIT_FAILURE);
		fd_out = dup(data->pipe_fd[1]);
	}
	if (data->outfile >= 0)
	{
		if (fd_out)
			close(fd_out);
		fd_out = data->outfile;
	}
	else if (!data->type)
		fd_out = dup(data->orig_output);
	if (data->pipe_fd[1])
		close(data->pipe_fd[1]);
	data->pipe_fd[1] = 0;
	return (fd_out);
}

int						install_in_fd(t_data *data)
{
	int fd_in;

	fd_in = 0;
	if (data->infile >= 0)
		fd_in = data->infile;
	else if (data->pipe_fd[0])
		fd_in = dup(data->pipe_fd[0]);
	else
		fd_in = dup(data->orig_input);
	if (data->pipe_fd[0])
		close(data->pipe_fd[0]);
	data->pipe_fd[0] = 0;
	return (fd_in);
}

void					parent_process(t_data *data, int pid)
{
	int status;

	status = 0;
	dup2(data->orig_input, 0);
	dup2(data->orig_output, 1);
	g_last_pid = pid;
	while (status != -1)
		status = process_status();
	errno = 0;
}
