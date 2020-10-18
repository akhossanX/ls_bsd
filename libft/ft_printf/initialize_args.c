/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:48:13 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/15 11:46:44 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Initializes s_args structure attributes.
*/

void	initialize_args(t_args *args)
{
	args->spec_index = -1;
	args->flag = 0;
	args->width = 0;
	args->precision = -1;
	args->spec = '\0';
	args->modifier = 0;
	args->result = NULL;
	args->decimal = NULL;
	args->fract = NULL;
}
