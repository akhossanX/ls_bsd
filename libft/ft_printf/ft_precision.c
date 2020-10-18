/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:40:56 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/24 19:41:02 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Returns a string according to a given precision
**	if the precision is less than len, we return
**	a truncated version of the string passed in args structure (args->result)
**	if the precision is zero it returns an empty string.
**	Deals only with C proper strings.
*/

void	is_s(t_args *args, int len)
{
	char	*tmp;

	tmp = args->result;
	if (args->precision == 0)
		args->result = ft_strdup("");
	else if (args->precision < len)
		args->result = ft_strsub(args->result, 0, args->precision);
	if (args->precision < len)
		ft_strdel(&tmp);
}

/*
**	Sets the resulting converted string to the precision
**	Given in the format string, if the precision is greater
**	than the actual length of the result, we left-padd zeros
**	to fill the gap, otherwise no padding is done.
**	Meant to deal only with unsigned numeric conversions(poubx)
*/

void	ft_poubx(t_args *args, int len)
{
	int		zeros;
	char	*tmp;
	char	*result;

	result = args->result;
	tmp = result;
	if (args->precision > len)
	{
		zeros = args->precision - len;
		args->result = padd(result, zeros, '0', 'L');
		ft_strdel(&tmp);
	}
}

/*
**	Handles the precision for signed and unsigned numeric
**	conversions "poubx" and "di" types.
**	keeps the sign in its place!!
*/

void	ft_precision(t_args *args)
{
	t_vars	var;

	var.elt = args->result;
	var.len = ft_strlen(var.elt);
	if (args->spec == 's' && args->precision >= 0)
		is_s(args, var.len);
	else if (ft_contains("poubxX", args->spec))
		ft_poubx(args, var.len);
	else if (ft_contains("id", args->spec))
	{
		var.sign = (var.elt[0] == '-');
		var.zeros = args->precision - (var.len - var.sign);
		if (args->precision > var.len - var.sign)
		{
			var.tmp = var.elt;
			args->result = padd(var.elt + var.sign, var.zeros, '0', 'L');
			ft_strdel(&var.tmp);
			var.tmp = args->result;
			args->result = var.sign ? \
							ft_strjoin("-", args->result) : args->result;
			if (var.sign)
				ft_strdel(&var.tmp);
		}
	}
}
