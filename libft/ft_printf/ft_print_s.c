/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:41:44 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/24 19:41:49 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Prints string arguments
*/

void	ft_print_s(t_args *args, t_vars *var)
{
	args->result = ft_strdup(va_arg(var->types_list, char *));
	if (!args->result)
		args->result = ft_strdup("(null)");
	if (!args->flag && !args->width && args->precision == -1)
		var->counter += ft_putstr_fd(var->fd, args->result);
	else
	{
		ft_precision(args);
		ft_width(args);
		var->counter += ft_putstr_fd(var->fd, args->result);
	}
	ft_strdel(&args->result);
}
