/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:33:54 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/11 17:21:30 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_entry_by_type(t_ls *ls, t_path *entry)
{
	t_path	**target;

	target = &ls->files;
	if ((ls->options & OPT_D) == 0 && (entry->st->st_mode & S_IFMT) == S_IFDIR)
			target = &ls->dirs;
	ls_path_append(target, entry);
}

struct stat	*new_stat(t_ls *ls)
{
	struct stat	*st;

	st = NULL;
	errno = 0;
	st = (struct stat *)ft_memalloc(sizeof(struct stat));
	if (errno != 0)
	{
		ls->err = errno;
		ls_handle_error(ls, NULL, LS_MAJOR_ERROR);
	}
	return (st);
}

int		set_stat(t_ls *ls, t_path *entry)
{
	entry->st = new_stat(ls);
	if (lstat(entry->fullpath, entry->st) == -1)
	{
		ls->err = errno;
		ls_handle_error(ls, entry->name, get_error_level(ls->err));
		return (0);
	}
	return (1);
}

void	process_arguments(t_ls *ls)
{
	t_path	*ptr;
	t_path	*next;

	ptr = ls->all;
	while (ptr != NULL)
	{
		next = ptr->next;
		if (set_stat(ls, ptr))
			add_entry_by_type(ls, ptr);
		else
		{
			ptr->next = NULL;
			ls_free_paths(ptr);
		}
		ptr = next;
	}
	ls->all = NULL;
}