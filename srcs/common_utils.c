/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:54:04 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/27 15:54:05 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 		process_status(void)
{
	int			child;
	int			status;

	if ((child = waitpid(-1, &status, 0)) == -1)
		return (-1);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = status | 128;
	if (last_pid == child)
		last_status = status;
	return (status);
}

t_data		*malloc_shell(char **env)
{
	t_data	*data;

	if (!(data = ft_calloc(1, sizeof(t_data))))
		ft_exit(data, EXIT_FAILURE);
	return (data);
}