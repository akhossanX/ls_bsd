/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 21:20:35 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/17 15:03:41 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	size_t		i;
	char		*joined;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + n;
	if (!(joined = ft_strnew(i)))
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strncat(joined, s2, n);
	return (joined);
}
