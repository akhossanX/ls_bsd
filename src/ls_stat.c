/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:33:54 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/08 13:43:22 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_stat(t_ls *ls, t_path *pathlist)
{
	errno = 0;
	while (pathlist)
	{
		if (!(pathlist->st = ft_memalloc(sizeof(struct stat))))
		{
			ls->errcode = errno;
			ls_handle_error(ls, NULL, LS_MAJOR_ERROR);
		}
		if (stat(pathlist->fullpath, pathlist->st) == -1)
		{
			ls->errcode = errno;
			free(pathlist->st);
			pathlist->st = NULL;
			ls_handle_error(ls, pathlist->fullpath, get_error_level(ls->errcode));
		}
		pathlist = pathlist->next;
	}
}
