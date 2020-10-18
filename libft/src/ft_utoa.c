/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:54:03 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/24 19:50:21 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*conversion(t_ull n, int nbr_chars)
{
	char	*to_string;
	int		i;
	t_ull	temp;

	temp = n;
	while (temp != 0)
	{
		nbr_chars++;
		temp = temp / 10;
	}
	if (!(to_string = (char *)ft_memalloc(nbr_chars)))
		return (NULL);
	to_string[nbr_chars] = '\0';
	i = nbr_chars - 1;
	while (n)
	{
		to_string[i--] = n % 10 + '0';
		n = n / 10;
	}
	return (to_string);
}

char	*ft_utoa(t_ull n)
{
	int nbr_chars;

	nbr_chars = 0;
	if (n == 0)
		return (ft_strdup("0"));
	return (conversion(n, nbr_chars));
}
