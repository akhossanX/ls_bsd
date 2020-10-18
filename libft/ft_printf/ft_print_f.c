/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:44:38 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/24 19:44:42 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Gets Mantissa form the binary floating point representation
**	and saves it into a string attribute in s_args structure.
**	the mantissa is 63 bit long, if the normalized bit is set
**	the mantissa is joined with "1", otherwise with "0".
*/

void	get_mantissa(t_args *args)
{
	int				i;
	char			*res;
	unsigned long	umantiss;

	umantiss = args->u_nion.floatbits.mantissa;
	args->mantiss = umantiss ? ft_strdup("0") : ft_strrep("0", 63);
	i = 0;
	if (umantiss)
	{
		while (i < 63)
		{
			if ((umantiss >> (62 - i)) & 1)
			{
				res = ft_large_pow(i + 1, "5");
				args->mantiss = sum_string(args->mantiss, res);
			}
			if (i < 62)
				args->mantiss = ft_strjoin_free(args->mantiss, ft_strdup("0"));
			i++;
		}
	}
	if (args->u_nion.floatbits.bit)
		args->mantiss = ft_strjoin_free(ft_strdup("1"), args->mantiss);
	else
		args->mantiss = ft_strjoin_free(ft_strdup("0"), args->mantiss);
}

/*
**	Rounds the fraction part of the floating point number.
*/

void	ft_fround(t_args *args)
{
	char	*s;
	char	*fsum;
	char	*carry;
	int		flen;
	int		slen;

	flen = ft_strlen(args->fract);
	if (!(s = is_roundable(args, flen)))
		return ;
	fsum = sum_string(s, ft_strdup(args->fract));
	slen = ft_strlen(fsum);
	if (slen > flen)
	{
		carry = ft_strsub(fsum, 0, slen - flen);
		args->decimal = sum_string(carry, args->decimal);
		args->fract = ft_strdup(fsum + slen - flen);
		ft_strdel(&fsum);
	}
	else
	{
		carry = args->fract;
		args->fract = fsum;
		ft_strdel(&carry);
	}
	args->fract[args->precision] = 0;
}

/*
**	Check whether the float number can be rounde,
**	we consider that a number is roundable if:
**	the digit after #precision of digits is > 5
**	or if it = 5 and at least one of the remaining
**	digits after 5 is not null.
**	for the decimal part when the digit after '.' is = 5
**	we round only if the right most digit of decimal part is odd
*/

char	*is_roundable(t_args *args, int flen)
{
	char	*s;
	int		i;
	int		last_digit;

	s = ft_strnew(flen);
	ft_memset(s, '0', flen);
	s[args->precision] = '5';
	if (args->fract[args->precision] == '5')
	{
		i = args->precision + 1;
		while (args->fract[i] && args->fract[i] == '0')
			i++;
		if (i == flen)
		{
			last_digit = args->decimal[ft_strlen(args->decimal) - 1] - '0';
			if (last_digit % 2)
				args->decimal = sum_string(args->decimal, ft_strdup("1"));
			return (NULL);
		}
	}
	return (s);
}

/*
**	Prints a floating point number.
*/

void	ft_print_f(t_args *args, t_vars *var)
{
	t_lldb	nbr;

	args->u_nion = ft_float_length(args, var);
	nbr = args->u_nion.ld;
	if (nbr != nbr)
		args->mantiss = ft_strdup("nan");
	else if (nbr == (1.0 / 0.0))
		args->mantiss = ft_strdup("inf");
	else if (nbr == (-1.0 / 0.0))
		args->mantiss = ft_strdup("-inf");
	else
	{
		split_float_parts(args);
		ft_fround(args);
	}
	join_dot_to_decimal(args);
	args->result = args->mantiss;
	ft_width(args);
	var->counter += ft_putstr_fd(var->fd, args->result);
	ft_strdel(&args->result);
}
