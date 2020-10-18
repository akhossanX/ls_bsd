/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:15:18 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/17 21:11:58 by aybouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrep(const char *s, size_t times)
{
	char	*dup;
	size_t	len;
	int		i;

	if (!s || times == 0)
		return (NULL);
	len = ft_strlen(s);
	if (!(dup = ft_strnew(ft_strlen(s) * times)))
		return (NULL);
	i = 0;
	while (times--)
	{
		ft_memcpy(dup + i, s, len);
		i += len;
	}
	dup[++i] = 0;
	return (dup);
}
