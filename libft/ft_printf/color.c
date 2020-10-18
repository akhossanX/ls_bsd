/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:11:23 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/25 14:58:43 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

/*
**	Iterates over the colors dispatcher
**	if there is a match in g_colors table
**	it returns the given color code.
*/

char	*get_color(char *str, int begin, int end)
{
	int		i;
	char	*color_name;

	color_name = ft_strsub(str, begin, end - begin + 1);
	i = 0;
	while (i < COLORS)
	{
		if (!ft_strcmp(color_name, g_colors[i].color_name))
		{
			ft_strdel(&color_name);
			return (g_colors[i].code);
		}
		i++;
	}
	ft_strdel(&color_name);
	return (NULL);
}

/*
**	Parses the color format string and sets the color, if any,
**	otherwise it prints '{' and leaves.
*/

void	set_color(t_vars *var)
{
	int		j;
	char	*color;

	j = var->i;
	if (var->str[j] == '{')
	{
		j++;
		while (var->str[j] != '}')
		{
			if (var->str[j] == '%' || !var->str[j])
			{
				var->counter += ft_putchar_fd(var->fd, var->str[var->i]);
				return ;
			}
			j++;
		}
		if ((color = get_color(var->str, var->i + 1, j - 1)))
			write(var->fd, color, ft_strlen(color));
		var->i = j;
	}
	else
		var->counter += ft_putchar_fd(var->fd, var->str[var->i]);
}
