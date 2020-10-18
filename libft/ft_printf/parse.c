/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:32:13 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/24 19:42:34 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Parses the format string and stores the masks of '+-#0 ' flags.
*/

void	get_flags(t_args *args, t_vars *var)
{
	while (ft_contains("-+#0 ", var->str[var->j]))
	{
		if (var->str[var->j] == '-')
		{
			args->flag |= MASK_MINUS;
			if (args->flag & MASK_ZERO)
				args->flag ^= MASK_ZERO;
		}
		if (var->str[var->j] == '0' && !(args->flag & MASK_MINUS))
			args->flag |= MASK_ZERO;
		args->flag |= var->str[var->j] == '#' ? MASK_HASH : 0;
		if (var->str[var->j] == '+')
		{
			args->flag |= MASK_PLUS;
			if (args->flag & MASK_SPACE)
				args->flag ^= MASK_SPACE;
		}
		if (var->str[var->j] == ' ')
		{
			if (!(args->flag & MASK_PLUS))
				args->flag |= MASK_SPACE;
		}
		var->j++;
	}
}

/*
**	Parses the format string and stores the length modifiers 'hlLzj' flags.
*/

void	get_modifier(t_args *args, t_vars *var)
{
	while (ft_contains("hlLzj", var->str[var->j]))
	{
		if (var->str[var->j] == 'h' && !(args->modifier & MASK_HH))
			args->modifier |= MASK_H;
		if (var->str[var->j] == 'h' && var->str[var->j + 1] == 'h')
		{
			args->modifier |= MASK_HH;
			args->modifier ^= args->modifier & MASK_H ? MASK_H : 0;
		}
		if (var->str[var->j] == 'l' && !(args->modifier & MASK_LL))
			args->modifier |= MASK_L;
		if (var->str[var->j] == 'l' && var->str[var->j + 1] == 'l')
		{
			args->modifier |= MASK_LL;
			args->modifier ^= args->modifier & MASK_L ? MASK_L : 0;
		}
		if (var->str[var->j] == 'L')
			args->modifier |= MASK_UPL;
		if (var->str[var->j] == 'z')
			args->modifier |= MASK_Z;
		if (var->str[var->j] == 'j')
			args->modifier |= MASK_J;
		var->j++;
	}
}

/*
**	Parses the format string and stores the minimum field width flag.
**	the MFW can also be retrieved from va_arg if '*' is given.
**	if its negative we set '-' flag and take the absolute value as width.
*/

void	get_width(t_args *args, t_vars *var)
{
	int		w;

	while (ft_isdigit(var->str[var->j]) || var->str[var->j] == '*')
	{
		if (ft_isdigit(var->str[var->j]))
		{
			w = ft_atoll(&var->str[var->j]);
			args->width = w > INT_MAX ? 0 : w;
			while (ft_isdigit(var->str[var->j]))
				var->j++;
		}
		if (var->str[var->j] == '*')
		{
			w = va_arg(var->types_list, int);
			if (w < 0)
			{
				w = w * -1;
				args->flag |= args->flag & MASK_MINUS ? 0 : MASK_MINUS;
				args->flag ^= args->flag & MASK_ZERO ? MASK_ZERO : 0;
			}
			args->width = w;
			var->j++;
		}
	}
}

/*
**	Gets the conversion type specifier
**	any character other than '-+#* .jzhlL' will be taken as type specifier
**	even if it's not supported.
*/

int		get_specifier(t_args *args, t_vars *var)
{
	while (ft_contains("-+#* .jzhlL", var->str[var->j]) \
			|| ft_isdigit(var->str[var->j]))
		var->j++;
	if (var->str[var->j])
	{
		args->spec_index = var->j;
		args->spec = var->str[var->j];
		return (1);
	}
	initialize_args(args);
	return (0);
}
