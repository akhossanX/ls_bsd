/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:46:17 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/04 14:33:20 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdelone(t_list **lst, void (*del)(void *, size_t))
{
	if (!lst || !*lst || !del)
		return ;
	if ((*lst)->content)
	{
		del((*lst)->content, (*lst)->content_size);
	}
	ft_memdel((void **)lst);
}
