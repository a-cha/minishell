/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 19:59:11 by pcatrina          #+#    #+#             */
/*   Updated: 2020/12/02 19:59:12 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_processing(t_data *data)
{
	pid_t pid;
	int status;
	char buff[10];

	if (pipe(data->pipe_fd) < 0)
		ft_exit(data, EXIT_FAILURE);
	printf("%d\n", data->pipe_fd[0]);
	printf("%d\n", data->pipe_fd[1]);

	pid = fork();
	if (pid == -1)
		ft_exit(data, EXIT_FAILURE);
	else if (pid == 0)
	{
		dup2(data->pipe_fd[1], 1);
		close(data->pipe_fd[0]);
//		dup2(data->pipe_fd[1], 1);
		child_process(data);
		close(data->pipe_fd[1]);
	}
	else
	{
		dup2(data->pipe_fd[0], 0);
		close(data->pipe_fd[1]);
		waitpid(pid, &status, 0);
//		read(data->pipe_fd[0], buff, 9);
//		write(data->orig_output, buff, 10);
//		parent_process(data, pid);
		close(data->pipe_fd[0]);
	}
}