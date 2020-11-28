/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:15:05 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/25 10:15:08 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_error(char *er_status, char *er_mess, int new_line)
{
	ft_putstr_fd("minishell : ", 2);
	if (er_status)
	{
		ft_putstr_fd(er_status, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(er_mess, 2);
	if (new_line)
		ft_putstr_fd("\n", 2);
}

void		ft_exit(t_data *data, int exit_status)
{
//	int e = data.exit;

	ft_arrayfree(data->args);
	ft_lstclear(&data->env, del_content);
	free_memory(data);
	if (exit_status == EXIT_FAILURE && errno)
		print_error(0, strerror(errno), 1);
	else
		ft_putendl_fd("exit", data->output);
	free_memory(data);
	exit(exit_status);
}
