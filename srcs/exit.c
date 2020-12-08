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

static int			ft_is_number(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[0] == '-')
			i++;
		if (ft_isdigit(str[i]) == 0)
			return (0);
	}
	return (1);
}

void				print_error(char *er_status, char *er_mess, int new_line)
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

static	int			error_arguments(t_data *data, int exit_status)
{
	if (data->args[0] && data->args[1])
	{
		if (data->args[2])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minihell > exit: too many arguments\n", 2);
			return (-1);
		}
		if (ft_is_number(data->args[1]) == 1)
			exit_status = ft_atoi(data->args[1]);
		else
		{
			ft_putstr_fd("exit :", 2);
			ft_putstr_fd(data->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_status = -1;
		}
	}
	return (exit_status);
}

void				ft_exit(t_data *data, int exit_status)
{
	if ((exit_status = error_arguments(data, exit_status)) == -1)
		return ;
	if (data->infile >= 0)
		close(data->infile);
	if (data->outfile >= 0)
		close(data->outfile);
	ft_arrayfree(data->args);
	ft_lstclear(&data->env, del_content);
	if (exit_status == EXIT_FAILURE && errno)
		print_error(0, strerror(errno), 1);
	else
		ft_putendl_fd("exit", 1);
	close(data->orig_output);
	close(data->orig_input);
	free_memory(data);
	exit(exit_status);
}
