/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 11:56:41 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/06 14:14:40 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_error_level(int error)
{
	if (error == ENOMEM || error == EMFILE || error == ENFILE)
		return (LS_MAJOR_ERROR);
	return (LS_MINOR_ERROR);
}

void	ls_free_paths(t_path *pathlist)
{
	t_path	*tmp;

	while (pathlist)
	{
		tmp = pathlist;
		ft_strdel(&pathlist->name);
		ft_strdel(&pathlist->parent);
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

void	ls_handle_error(t_ls *ls, const char *arg, int error_level)
{
	if (error_level == LS_MAJOR_ERROR)
	{
		ft_dprintf(STDERR, "%s: %s\n", ls->prog, strerror(ls->errcode));
		ls_clean_all(ls);
		exit(EXIT_FAILURE);
	}
	else
		ft_dprintf(STDERR, "%s: %s: %s\n", 
			ls->prog, arg, strerror(ls->errcode));
}
