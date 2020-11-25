/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:31:18 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/25 14:31:20 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	errors(char *error, int err_code)
{
	ft_putstr_fd(error, 1);
	ft_putnbr_fd(err_code, 1);
	return (err_code);
}
