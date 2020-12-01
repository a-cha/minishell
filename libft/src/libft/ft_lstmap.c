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
	t_list	*copy;
	t_list	*save;
	void	*new;

	if (!lst || !f || !(new = f(lst->content)) || !(copy = ft_lstnew(new)))
		return (NULL);
	save = copy;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new = f(lst->content)) || !(copy->next = ft_lstnew(new)))
		{
			ft_lstclear(&save, del);
			return (NULL);
		}
		copy = copy->next;
	}
	return (save);
}
