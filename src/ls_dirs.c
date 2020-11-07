/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:23:53 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/07 14:45:02 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_process_dirs(t_ls *ls, t_path **dirs)
{
	if (ls->options & OPT_F) // DO NOT sort
	{
		if (ls->options & OPT_L)
			set_stat(ls, *dirs);
	}
	else
	{
		ls->sort_type = get_sort_type(ls->options);
		if ((ls->options & OPT_L) ||  ls->sort_type != ASCII_SORT)
			set_stat(ls, *dirs);
		ls_sort(ls, dirs);
	}
}

char    *get_full_path(const char *parent, const char *entry)
{
    char    *fullpath;
    char    *tmp;

    errno = 0;
    if (!parent)
        return (ft_strdup(entry));
    if (!(tmp = ft_strjoin(parent, "/")))
        return (NULL);
    fullpath = ft_strjoin(tmp, entry);
    ft_strdel(&tmp);
    return (fullpath);
}

/*
**	Closes the directory stream if it is already opened
**	and sets the pointer to null
*/

void	ft_ls_closedir(DIR **dirp)
{
	if (*dirp != NULL)
		(void)closedir(*dirp);
	*dirp = NULL;
}

/*
**	Reads the content of a directory stream and returns its content
**	On error it returns NULL and sets ls->errcode according to errno
*/

t_path	*ls_readdir(t_ls *ls, const char *dir)
{
	t_path	*dir_content_list;

	dir_content_list = NULL;
	while ((ls->de = readdir(ls->dp)) != NULL)
		ls_save_path(ls, &dir_content_list, dir, ls->de->d_name);
	if (ls->de == NULL && errno)
	{
		ls->errcode = errno;
		ls_free_paths(dir_content_list);
		return (NULL);
	}
	ft_ls_closedir(&ls->dp);
	return (dir_content_list);
}

/*
**	Opens a directory streams, reads its content and stores it
**	in a list of paths (directory entries)
**	On error it returns NULL and sets ls->errcode appropriately
**	this ls->errcode is fetched later, based on the level of danger,
**	we decide what to do accordingly.
*/

t_path  *ls_get_dir_content(t_ls *ls, t_path *dir)
{
    char            *fullpath;
    t_path          *content;

    errno = 0;
    if (!(fullpath = get_full_path(dir->parent, dir->name)))
    {
        ls->errcode = errno;
        return (NULL);
    }
    if ((ls->dp = opendir(fullpath)))
    {
		content = ls_readdir(ls, fullpath);
		ft_strdel(&fullpath);
		return (content);
    }
	ls->errcode = errno;
	ft_strdel(&fullpath);
	ls_handle_error(ls, dir->name, get_error_level(ls->errcode));
    return (NULL);
}


void	ls_dirs(t_ls *ls, t_path *dirs)
{
	t_path	*ptr;
	t_path	*dir_content;

	if (dirs == NULL)
	{
		if (ls->errcode)
			ls_handle_error(ls, NULL, get_error_level(ls->errcode));
		return ;
	}
	ptr = dirs;
	while (ptr != NULL)
	{
		dir_content = ls_get_dir_content(ls, ptr);
		ls_process_dirs(ls, &dir_content);
		ls_display(ls, dir_content);
		if (ls->options & OPT_CAPR)
			ls_dirs(ls, dir_content);
		ls_free_paths(dir_content);
		ptr = ptr->next;
	}
}
