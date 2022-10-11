/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:21:56 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/08 12:16:58 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_free_paths(t_path *pathlist)
{
	t_path	*tmp;

	while (pathlist)
	{
		tmp = pathlist;
		ft_strdel(&pathlist->name);
		ft_strdel(&pathlist->fullpath);
		free(pathlist->st);
		ft_strdel(&pathlist->usrname);
		ft_strdel(&pathlist->grpname);
		ft_strdel(&pathlist->xattr);
		pathlist = pathlist->next;
		free(tmp);
	}
}

void	ls_clean_all(t_ls *ls)
{
	ls_free_paths(ls->all);
	ls->all = NULL;
	ls_free_paths(ls->dirs);
	ls->dirs = NULL;
	ls_free_paths(ls->files);
	ls->files = NULL;
	free(ls);
}
