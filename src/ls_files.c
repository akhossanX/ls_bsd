/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:22:45 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/07 14:42:39 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_sort	get_sort_type(int options)
{
	if (options & OPT_T)
	{
		if (options & OPT_U)
			return (ATIME_SORT);
		if (options & OPT_C)
			return (CTIME_SORT);
		return (MTIME_SORT);
	}
	if (options & OPT_CAPS)
		return (SIZE_SORT);
	return (ASCII_SORT);
}

void	ls_process_files(t_ls *ls)
{
	t_path	*target;

	target = NULL;
	if (ls->all)
		target = ls->all;
	else if (ls->files)
		target = ls->files;
	if (ls->options & OPT_F) // DO NOT sort
	{
		if (ls->options & OPT_L)
			set_stat(ls, target);
	}
	else
	{
		ls->sort_type = get_sort_type(ls->options);
		if ((ls->options & OPT_L) ||  ls->sort_type != ASCII_SORT)
			set_stat(ls, target);
		ls_sort(ls, &target);
	}
	ls_display(ls, target);
}
