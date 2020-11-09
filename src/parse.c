/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:47:21 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/09 13:07:56 by akhossan         ###   ########.fr       */
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

int		ls_is_dir(t_ls *ls, const char *name)
{
	DIR	*dirp;

	errno = 0;
	dirp = opendir(name);
	if (dirp == NULL)
	{
		ls->errcode = errno;
		return (0);
	}
	closedir(dirp);
	return (1);
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
			ls->operands++;
			get_cli_operand(ls, argv[i]);
		}
		i++;
	}
	if (!ls->all && !ls->dirs && !ls->files && ls->operands == 0)
		ls_save_path(ls, &ls->dirs, NULL, ".");
	if (ls->errcode == ENOTDIR)
		ls->errcode = 0;
}

void	get_cli_as_files(t_ls *ls, const char *arg)
{
	DIR	*dp;
	//TODO:
	// no need to open the file

	errno = 0;
	dp = opendir(arg);
	if (dp == NULL && errno != ENOTDIR)
	{
		ls->errcode = errno;
		ls_handle_error(ls, arg, get_error_level(ls->errcode));
	}
	else
	{
		ls_closedir(&dp);
		ls_save_path(ls, &ls->all, NULL, arg);
	}
}

void	get_cli_operand(t_ls *ls, const char *arg)
{
	errno = 0;
	if (ls->options & OPT_D)
		get_cli_as_files(ls, arg);
	else
	{
		if (ls_is_dir(ls, arg))
		{
			ls_save_path(ls, &ls->dirs, NULL, arg);
			ls->dir_count++;
		}
		else
		{
			if (get_error_level(ls->errcode) == LS_MINOR_ERROR)
			{
				if (ls->errcode == ENOTDIR)
					ls_save_path(ls, &ls->files, NULL, arg);
				else
					ls_handle_error(ls, arg, LS_MINOR_ERROR);
			}
			else
				ls_handle_error(ls, arg, LS_MAJOR_ERROR);
		}
	}
}

int		is_valid_option(const char opt)
{
	int		i;

	i = 0;
	while (i < NOPTIONS)
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
