/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:47:21 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/05 14:21:55 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	filter_options(t_ls *ls, int flag)
{
	ls->options |= flag;
	if (flag == OPT_L)
	{
		ls->options & OPT_1 ? ls->options ^= OPT_1 : 0;
		ls->options & OPT_CAPC ? ls->options ^= OPT_CAPC : 0;
	}
	else if (flag == OPT_1)
	{
		ls->options & OPT_L ? ls->options ^= OPT_L : 0;
		ls->options & OPT_CAPC ? ls->options ^= OPT_CAPC : 0;
	}
	else if (flag == OPT_CAPC)
	{
		ls->options & OPT_L ? ls->options ^= OPT_L : 0;
		ls->options & OPT_1 ? ls->options ^= OPT_1 : 0;
	}
	flag == OPT_C && (ls->options & OPT_U) ? ls->options ^= OPT_U : 0;
	flag == OPT_U && (ls->options & OPT_C) ? ls->options ^= OPT_C : 0;
	flag == OPT_CAPR && (ls->options & OPT_D) ? ls->options ^= OPT_CAPR : 0;
}

void	parse_cli_arguments(t_ls *ls, char **argv)
{
	int		i;

	get_cli_options(ls, argv);
	i = 0;
	while (argv[i])
	{
		if (*argv[i] != '-' || i > ls->optend)
		{
			if (ls->options & OPT_D)
			{
				;//save all entries in "all" list	
			}
			else
				;//save l9lawi 3la hasab wach file wla dir
		}
		i++;
	}
}

int		is_valid_option(const char opt)
{
	int		i;

	i = 0;
	while (i < OPTIONS)
	{
		if (g_options[i].option == opt)
			return (g_options[i].code);
		i++;
	}
	return (0);
}

void		get_cli_options(t_ls *ls, char **argv)
{
	int		i;
	int		j;
	int		optcode;

	i = 0;
	while (argv[i] && !ft_strequ(argv[i], "--"))
	{
		if (*argv[i] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				if ((optcode = is_valid_option(argv[i][j])))
					filter_options(ls, optcode);
				else
					ls_usage(ls, argv[i][j]);
				j++;
			}
		}
		i++;
	}
	if (argv[i])
		ls->optend = i;
}

void	ls_usage(t_ls *ls, const char option)
{
	ft_dprintf(STDERR, "%s: %s %c\n", ls->prog, "illegal option --", option);
	free(ls);
	exit(1);	
}
