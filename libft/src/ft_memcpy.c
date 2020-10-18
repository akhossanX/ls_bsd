/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:27:02 by aybouras          #+#    #+#             */
/*   Updated: 2019/04/03 13:05:20 by aybouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*tmp_src;
	char	*tmp_dst;

	tmp_src = (char *)src;
	tmp_dst = (char *)dst;
	i = 0;
	while (i < n)
	{
		*tmp_dst = *tmp_src;
		tmp_dst++;
		tmp_src++;
		i++;
	}
	return (dst);
}
