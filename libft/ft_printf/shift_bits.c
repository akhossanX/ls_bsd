/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouras <aybouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:13:47 by aybouras          #+#    #+#             */
/*   Updated: 2019/11/24 19:45:32 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nbase_length(t_ull nbr, int shift)
{
	t_ull	nb;
	int		len;

	nb = nbr;
	len = 1;
	while (nb >>= shift)
		len++;
	return (len);
}

/*
**	Converts an unsigned number to a given base,
**	the base is indicated by @shift parameter
**	7 = 111 for octal, 15 = 1111 for hexadecimal...
**	saves the result in a @convert string passed as parameter
*/

void		shift_bits(char **convert, t_ull nbr, int mask, int shift)
{
	int			len;
	static char *str = "0123456789abcdef";

	len = nbase_length(nbr, shift);
	*convert = ft_strnew(len);
	while (len--)
	{
		(*convert)[len] = str[nbr & mask];
		nbr >>= shift;
	}
}
