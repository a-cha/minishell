/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:44:29 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/28 16:44:40 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					free_memory(void *memory)
{
	free(memory);
	memory = NULL;
}

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
	data->flag_redir = 0;
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
	last_pid = pid;
	while (status != -1)
		status = process_status();
	errno = 0;
}

/*
** Returns max value
*/

int			max(int n1, int n2)
{
	return (n1 > n2 ? n1 : n2);
}

/*
** Functions for correct use of the ft_lstmap
*/

void		del_content(void *elem)
{
	t_env	*env;

	env = elem;
	free_memory(env->env_name);
	free_memory(env->env_cont);
	free_memory(elem);
}

void		*copy_t_env(void *elem)
{
	t_env	*env;
	t_env	*el_env;

	if ((env = (t_env *)malloc(sizeof(t_env))))
	{
		el_env = elem;
		if (!(env->env_name = ft_strdup(el_env->env_name)))
		{
			free_memory(env);
			return (NULL);
		}
		if (!(env->env_cont = ft_strdup(el_env->env_cont)))
		{
			free_memory(env);
			free_memory(env->env_name);
			return (NULL);
		}
		env->is_equal = el_env->is_equal;
	}
	return (env);
}
