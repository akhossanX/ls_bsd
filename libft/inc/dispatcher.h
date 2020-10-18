/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 21:48:46 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/24 19:38:53 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCHER_H
# define DISPATCHER_H
# include "ft_printf.h"

typedef void		(*t_width_func)(t_args *arg);

typedef struct		s_width_dispatch
{
	char			spec;
	t_width_func	width;
}					t_width_dispatch;

void				ft_alternate(t_args *args);
void				ft_string(t_args *args);
void				ft_numeric(t_args *args);

t_width_dispatch	g_funcs[] =
{
	{'d', ft_numeric},
	{'i', ft_numeric},
	{'u', ft_numeric},
	{'s', ft_string},
	{'p', ft_alternate},
	{'x', ft_alternate},
	{'X', ft_alternate},
	{'o', ft_alternate},
	{'b', ft_alternate},
	{'f', ft_numeric}
};

#endif
