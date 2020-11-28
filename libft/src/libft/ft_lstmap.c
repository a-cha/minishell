/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:07:38 by sadolph           #+#    #+#             */
/*   Updated: 2020/05/09 16:25:32 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *copy;
	t_list *save;

	if (!lst || !f || !(copy = ft_lstnew(f(lst->content))))
		return (NULL);
	save = copy;
	while (lst->next)
	{
		lst = lst->next;
		if (lst && !(copy->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&save, del);
			return (NULL);
		}
		copy = copy->next;
	}
	return (save);
}
