/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:48:48 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/24 19:45:22 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Padds @rest characters @c to the @side side
**	@c: corresponds to the character to be padded
**	@rest: the number of occurences to be padded
**	@side: 'R' for right, 'L' for left.
*/

char	*padd(char *element, int rest, char c, char side)
{
	char	*str;
	char	*tmp;

	str = rest <= 0 ? NULL : ft_strnew(rest);
	if (rest <= 0)
		return (ft_strdup(element));
	ft_memset(str, c, rest);
	tmp = str;
	if (side == 'R')
		str = ft_strjoin(element, str);
	else
		str = ft_strjoin(str, element);
	ft_strdel(&tmp);
	return (str);
}
