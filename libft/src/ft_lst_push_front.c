/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:41:25 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/04 15:22:56 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lst_push_front(t_list **alst, t_list *new)
{
	if (!alst || !new)
		return ;
	new->next = (*alst);
	*alst = new;
}
