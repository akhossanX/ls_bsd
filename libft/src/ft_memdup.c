/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:34:02 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/13 19:34:04 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *s, size_t n)
{
	void	*mem;

	if (n == 0)
		return (NULL);
	mem = ft_memalloc(n);
	if (mem == NULL)
		return (NULL);
	ft_memmove(mem, s, n);
	return (mem);
}
