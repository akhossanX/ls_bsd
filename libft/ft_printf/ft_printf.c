/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 11:48:00 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/15 21:52:41 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Escape 42 Norminette shit rules 😎
*/

static void	ft_helper(t_args *args, t_vars *var)
{
	while (var->str[++var->i])
	{
		if (var->str[var->i] == '%')
		{
			initialize_args(args);
			var->j = var->i + 1;
			if (!var->str[var->j])
				break ;
			if (!get_specifier(args, var))
			{
				var->i = var->j;
				continue ;
			}
			var->j = var->i + 1;
			get_flags(args, var);
			get_width(args, var);
			get_precision(args, var);
			get_modifier(args, var);
			manage_args(args, var);
			var->i = args->spec_index;
		}
		else
			set_color(var);
	}
}

/*
**	Our evil ft_dprintf trying to imitate dprintf monster 😈
*/

int			ft_printf(const char *format, ...)
{
	t_args args;
	t_vars var;

	if (!format)
		exit(1);
	va_start(var.types_list, format);
	var.fd = 1;
	var.counter = 0;
	var.str = (char *)format;
	var.i = -1;
	ft_helper(&args, &var);
	va_end(var.types_list);
	return (var.counter);
}

/*
**	Works same as ft_printf, however it prints
**	the result to a given file descriptor fd.
*/

int			ft_dprintf(int fd, const char *format, ...)
{
	t_args args;
	t_vars var;

	if (!format || fd < 0)
		exit(1);
	va_start(var.types_list, format);
	var.fd = fd;
	var.counter = 0;
	var.str = (char *)format;
	var.i = -1;
	ft_helper(&args, &var);
	va_end(var.types_list);
	return (var.counter);
}
