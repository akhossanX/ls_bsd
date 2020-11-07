/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:33:54 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/07 13:35:33 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_stat(t_ls *ls, t_path *pathlist)
{
	errno = 0;
	while (pathlist)
	{
		if (lstat(pathlist->name, &pathlist->st) == -1)
		{
			ls->errcode = errno;
			ls_handle_error(ls, pathlist->name, get_error_level(ls->errcode));
		}
		pathlist = pathlist->next;
	}
}
