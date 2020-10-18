/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:55:22 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/15 11:43:03 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Prints signed decimal conversions (d, i)
*/

void	ft_print_d(t_args *args, t_vars *var)
{
	t_ll	x;
	char	*tmp;

	x = ft_signed(args, var);
	args->result = ft_ltoa(x);
	if (!args->flag && !args->width && args->precision == -1)
	{
		var->counter += ft_putstr_fd(var->fd, args->result);
		ft_strdel(&args->result);
	}
	else
	{
		if (!args->precision && !x)
		{
			tmp = args->result;
			args->result = ft_strdup("");
			ft_strdel(&tmp);
		}
		else
			ft_precision(args);
		ft_width(args);
		var->counter += ft_putstr_fd(var->fd, args->result);
		ft_strdel(&args->result);
	}
}
