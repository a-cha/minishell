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

static int             for_return(t_data *data, void (*f)(t_data *data))
{
	f(data);
	return (0);
}

int 				our_command(t_data *data)
{
	if(data->args[0])
	{
		if (!(ft_strcmp(data->args[0], "cd")))
			return(for_return(data, cd));
		else if (!(ft_strcmp(data->args[0], "pwd")))
			return(for_return(data, pwd));
		else if (!(ft_strcmp(data->args[0], "echo")))
			return(for_return(data, echo));
		else if (!(ft_strcmp(data->args[0], "export")))
			return(for_return(data, env_export));
		else if (!(ft_strcmp(data->args[0], "unset")))
			return(for_return(data, env_unset));
		else if (!(ft_strcmp(data->args[0], "env")))
		{
			test_env_list(&data->env);
			return (0);
		}
		else if (!(ft_strcmp(data->args[0], "exit")))
		{
			ft_exit(data, last_status);
			return (0);
		}
		return (1);
	}
	return (1);
}

void				parent_process(t_data *data, int pid)
{
	int status;

	status = 0;
//	dup2(data->orig_input, 0);
//	dup2(data->orig_output, 1);
	last_pid = pid;
	while (status != -1)
		status = process_status();
	errno = 0;
}

void				child_process(t_data *data)
{
	char		**ar;
	char		*str;
	char 		**env;

	last_status = 0;
//	if (data->pipe_fd[0])
//		close(data->pipe_fd[0]);
	if (our_command(data) == 0)
		exit(EXIT_SUCCESS);
	if (!(ar = ft_split(find_env(&data->env, "PATH"), ':')))
		ft_exit(data, EXIT_FAILURE);
	if ((str = is_corr_path(ar, data->args[0])) == NULL)
		str = data->args[0];
	if (!(env = list_to_array(data)))
	{
		free_memory(str);
		ft_arrayfree(ar);
		ft_exit(data, EXIT_FAILURE);
	}
	execve((const char *)str, data->args, env);
//	need to set correct errno and write error to 2 fd
	if (errno == 13)
	{
		printf("minishell: %s: %s\n", str, strerror(errno));
		free_memory(str);
		ft_arrayfree(env);
//		ft_exit(data, 126);
		exit(126);
	}
	free_memory(str);
	ft_arrayfree(env);
//	ft_exit(data, 127);
	exit(127);
}

int			install_out_fd(t_data *data)
{
	int fd_out;

	fd_out = 0;
	if (data->type)
	{
		if (pipe(data->pipe_fd) == -1)
			ft_exit(data, EXIT_FAILURE);
		fd_out = dup(data->pipe_fd[1]);
		printf("fd_out %d\n", data->pipe_fd[1]);
	}
	if (data->outfile)
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

int 			install_in_fd(t_data *data)
{
	int fd_in;

	fd_in = 0;
	if (data->infile)
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

void				processing_pipe(t_data *data)
{
	int fd_in;
	int fd_out;
	int	pid;

	pid = 0;
	fd_in = install_in_fd(data);
	fd_out = install_out_fd(data);
	printf("fd_in %d\n", data->pipe_fd[0]);
	printf("fd_out %d\n", data->pipe_fd[1]);
	dup2(fd_in, 0);
	close(fd_in);
	dup2(fd_out, 1);
	close(fd_out);
//	printf("fd_in: %d, fd_out: %d\n", fd_in, fd_out);
	pid = fork();
	if (pid == -1)
		ft_exit(data, EXIT_FAILURE);
	else if (pid == 0)
		child_process(data);
//	if (!data->type)
//		parent_process(data, pid);
}
