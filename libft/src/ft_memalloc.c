/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 22:48:16 by aybouras          #+#    #+#             */
/*   Updated: 2019/04/05 10:31:17 by aybouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *fresh_mem;

	fresh_mem = NULL;
	fresh_mem = (void *)malloc(size);
	if (fresh_mem == NULL)
		return (NULL);
	ft_bzero(fresh_mem, size);
	return (fresh_mem);
}
