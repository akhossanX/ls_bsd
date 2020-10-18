/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_arg_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:13:26 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/24 19:45:52 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Casts the va_arg argument according to the given length modifier.
**	operates only on unsigned values.
**	it supports: 'l', 'll', 'j', 'z', 'h', 'hh'.
*/

t_ull	ft_unsigned(t_args *args, t_vars *var)
{
	t_ull unsign_ed;

	if (args->modifier & MASK_L)
		unsign_ed = va_arg(var->types_list, unsigned long);
	else if (args->modifier & MASK_LL)
		unsign_ed = va_arg(var->types_list, unsigned long long);
	else if (args->modifier & MASK_Z)
		unsign_ed = va_arg(var->types_list, size_t);
	else if (args->modifier & MASK_J)
		unsign_ed = va_arg(var->types_list, uintmax_t);
	else if (ft_contains("ouxX", args->spec))
		unsign_ed = va_arg(var->types_list, unsigned int);
	else
		unsign_ed = va_arg(var->types_list, unsigned long long);
	if (args->modifier & MASK_H)
		unsign_ed = (unsigned short)unsign_ed;
	else if (args->modifier & MASK_HH)
		unsign_ed = (unsigned char)unsign_ed;
	return (unsign_ed);
}

/*
**	Casts the va_arg argument according to the given length modifier.
**	operates only on unsigned values.
**	it supports: 'l', 'll', 'j', 'z', 'h', 'hh'.
*/

t_ll	ft_signed(t_args *args, t_vars *var)
{
	t_ll sign_ed;

	if (args->modifier & MASK_L)
		sign_ed = va_arg(var->types_list, long);
	else if (args->modifier & MASK_LL)
		sign_ed = va_arg(var->types_list, long long);
	else if (args->modifier & MASK_Z)
		sign_ed = va_arg(var->types_list, size_t);
	else if (args->modifier & MASK_J)
		sign_ed = va_arg(var->types_list, intmax_t);
	else
	{
		sign_ed = va_arg(var->types_list, int);
		if (args->modifier & MASK_H)
			sign_ed = (short)sign_ed;
		else if (args->modifier & MASK_HH)
			sign_ed = (char)sign_ed;
	}
	return (sign_ed);
}

/*
**	According to the length modifier, this function stores the appropriate
**	format type into a union for floating point formats.
**	supoorts: 'l', 'L'.
*/

t_float	ft_float_length(t_args *args, t_vars *var)
{
	t_float u;

	if (args->modifier & MASK_L)
		u.ld = va_arg(var->types_list, double);
	else if (args->modifier & MASK_UPL)
		u.ld = va_arg(var->types_list, long double);
	else
		u.ld = va_arg(var->types_list, double);
	return (u);
}
