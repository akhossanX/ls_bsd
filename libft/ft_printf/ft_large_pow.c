/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_large_pow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:09:43 by aybouras          #+#    #+#             */
/*   Updated: 2019/11/24 19:40:41 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Returns the power of a number @nb
**	@nb is the string representation of an integer number
**	pow is the exponent.
**	We used the 'Divide and Conquer' algorithm.
*/

char	*ft_large_pow(unsigned long long pow, char *nb)
{
	char	*tmp;

	if (pow == 0)
		return (ft_strdup("1"));
	tmp = ft_large_pow(pow / 2, nb);
	if (pow % 2 == 0)
		return (multiply_string(tmp, tmp, 0));
	else
		return (multiply_string(multiply_string(tmp, tmp, 0), nb, 0));
}
