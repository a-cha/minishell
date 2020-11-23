/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:57:05 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 13:57:05 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_content(void *elem)
{
	free(elem);
	elem = NULL;
}

void	*apply_nothing(void *elem)
{
	return (elem);
}
