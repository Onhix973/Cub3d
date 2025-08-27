/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:48:56 by tlutz             #+#    #+#             */
/*   Updated: 2024/11/25 18:33:18 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*swap;
	void	*content;

	if (!f || !del)
		return (0);
	new = NULL;
	while (lst)
	{
		content = f(lst->content);
		swap = ft_lstnew(content);
		if (!swap)
		{
			del(content);
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, swap);
		lst = lst->next;
	}
	return (new);
}
