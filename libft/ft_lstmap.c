/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:31:10 by abuzdin           #+#    #+#             */
/*   Updated: 2022/01/19 10:26:49 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*lst_new_head;

	if (!lst || !f)
		return (NULL);
	lst_new_head = ft_lstnew(f(lst->content));
	lst_new = lst_new_head;
	lst = lst->next;
	while (lst)
	{
		lst_new->next = ft_lstnew(f(lst->content));
		if (!(lst_new->next))
		{
			ft_lstclear(&lst_new_head, del);
			return (NULL);
		}
		lst = lst->next;
		lst_new = lst_new->next;
	}
	return (lst_new_head);
}
