/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:31:35 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/04 14:30:40 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **lst, void (*del)(void *, size_t))
{
	t_list	**tmp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		tmp = &((*lst)->next);
		ft_lstdelone(lst, del);
		lst = tmp;
	}
}
