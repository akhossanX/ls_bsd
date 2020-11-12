/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:22:45 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/08 14:19:16 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_files(t_ls *ls)
{
	if (ls->sort_type != ASCII_SORT && ls->sort_type != NO_SORT)
		ls->files = ls_sort(ls->files, ls->sort_type, ls->options & OPT_R);
	ls_display(ls, ls->files);
}