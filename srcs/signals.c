/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:58:25 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/26 16:58:27 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_quit()
{
	int	exit_status;

	if ((exit_status = process_status()) == -1)
		return ;
	else if(exit_status == 131)
		write(2, "Quit: 3\n", 8);
}

static void	sig_int()
{
	int	exit_status;

	if ((exit_status = process_status()) == -1)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("Вводи > ", 1);
	}
	else
		ft_putstr_fd("\n", 1);

}

void		signal_oper()
{
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);
}