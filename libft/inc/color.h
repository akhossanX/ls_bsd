/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:06:25 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/06 21:38:52 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include "ft_printf.h"
# define COLORS	37

/*
**	Set of foreground and background colors;
**	the structure s_color defines two attributes:
**	@color_name: string
**		represents the color name, for background colors we prefixed
**		their names with a leading 'b_' to distiguish them from foreground
**		colors. '{eoc}' sets the foreground color to its default value,
**		as well as '{eobc}' sets the default background color, '{eoall}' resets
**		all the colors to default(removes all formatting and color attributes),
**		'{eoftxt}' resets the text format to default.
**	@code: string
**		The color code recognized by terminal
*/

typedef struct		s_color
{
	char	*color_name;
	char	*code;
}					t_color;

t_color	g_colors[] =
{
	{"black", "\e[30m"},
	{"red", "\e[31m"},
	{"green", "\e[32m"},
	{"yellow", "\e[33m"},
	{"blue", "\e[34m"},
	{"magneta", "\e[35m"},
	{"cyan", "\e[36m"},
	{"light gray", "\e[37m"},
	{"dark gray", "\e[90m"},
	{"light red", "\e[91m"},
	{"light green", "\e[92m"},
	{"light yellow", "\e[93m"},
	{"light blue", "\e[94m"},
	{"light magneta", "\e[95m"},
	{"light cyan", "\e[96m"},
	{"white", "\e[97m"},
	{"b_black", "\e[40m"},
	{"b_red", "\e[41m"},
	{"b_green", "\e[42m"},
	{"b_yellow", "\e[43m"},
	{"b_blue", "\e[44m"},
	{"b_magneta", "\e[45m"},
	{"b_cyan", "\e[46m"},
	{"b_light_gray", "\e[47m"},
	{"b_dark_gray", "\e[100m"},
	{"b_light_red", "\e[101m"},
	{"b_light_green", "\e[102m"},
	{"b_light_yellow", "\e[103m"},
	{"b_light_blue", "\e[104m"},
	{"b_light_magneta", "\e[105m"},
	{"b_light_cyan", "\e[106m"},
	{"b_white", "\e[107m"},
	{"bold", "\e[1m"},
	{"eoc", "\e[39m"},
	{"eobc", "\e[49m"},
	{"eoall", "\e[0m"},
	{"eoftxt", "\e[0m"}
};

#endif
