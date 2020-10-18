/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:45:55 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/24 19:43:19 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	checks if the result is not a number (NaN)
*/

int		is_nan(t_args *arg)
{
	int	flag;

	flag = !ft_strcmp(arg->result, "nan");
	return (flag);
}

/*
** after managing sign inf might be preceded by -, +, space or nothing
*/

int		is_inf(t_args *arg)
{
	int	flag;

	flag = !ft_strcmp(arg->result, "inf") || !ft_strcmp(arg->result, "-inf") \
		|| !ft_strcmp(arg->result, "+inf") || !ft_strcmp(arg->result, " inf");
	return (flag);
}

/*
** if the argument is positive we preppend + or space
** if it's negative there is a sign by default '-'.
** we consider that there is a sign as long as we prepend "+"/" "
** to the result.
*/

int		manage_sign(t_args *arg, int sign)
{
	if (!sign)
	{
		if ((arg->flag & MASK_PLUS) && arg->spec != 'u')
		{
			if (!is_nan(arg) || is_inf(arg))
			{
				arg->result = ft_strjoin_free(ft_strdup("+"), arg->result);
				return (1);
			}
			return (0);
		}
		else if ((arg->flag & MASK_SPACE) && arg->spec != 'u')
		{
			if (!is_nan(arg) || is_inf(arg))
			{
				arg->result = ft_strjoin_free(ft_strdup(" "), arg->result);
				return (1);
			}
			return (0);
		}
		return (0);
	}
	return (1);
}
