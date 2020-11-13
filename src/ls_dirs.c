/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:23:53 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/12 12:02:26 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Closes the directory stream if it is already opened
**	and sets the pointer to null
*/

void	ls_closedir(DIR **dirp)
{
	if (*dirp != NULL)
		(void)closedir(*dirp);
	*dirp = NULL;
}

/*
**	Reads the content of a directory stream and returns its content
**	On error it returns NULL and sets ls->err according to errno
*/

t_path	*ls_readdir(t_ls *ls, t_path *dir)
{
	t_path	*dir_content_list;
	t_path	*new;

	ft_bzero((void *)&ls->display, sizeof(t_display));// For each dir we initialize all display data to 0
	dir_content_list = NULL;
	while ((ls->de = readdir(ls->dp)) != NULL)
	{
		new = ls_save_path(ls, &dir_content_list, dir->fullpath, ls->de->d_name);
		set_stat(ls, new);
	}
	if (ls->de == NULL && errno)
	{
		ls->err = errno;
		ls_free_paths(dir_content_list);
		ls_handle_error(ls, dir->name, get_error_level(ls->err));
		return (NULL);
	}
	ls_closedir(&ls->dp);
	return (dir_content_list);
}

/*
**	Opens a directory streams, reads its content and stores it
**	in a list of paths (directory entries)
**	On error it returns NULL and sets ls->err appropriately
**	this ls->err is fetched later, based on the level of danger,
**	we decide what to do accordingly.
*/

t_path  *ls_get_dir_content(t_ls *ls, t_path *dir)
{
    t_path          *content;

    errno = 0;
    if ((ls->dp = opendir(dir->fullpath)))
    {
		content = ls_readdir(ls, dir);
		return (content);
    }
	ls->err = errno;
	ls_handle_error(ls, dir->name, get_error_level(ls->err));
    return (NULL);
}

int		ls_isdir(t_path *path)
{
	return ((path->st->st_mode & S_IFMT) == S_IFDIR);
}

void	ls_dirs(t_ls *ls, t_path *dirs, int cli_or_recurse)
{
	t_path	*content;

	while (dirs != NULL)
	{
		if ((cli_or_recurse == RECURSE && 
			(ft_strequ(dirs->name, ".") || ft_strequ(dirs->name, ".."))) ||
			!ls_isdir(dirs))
		{
			dirs = dirs->next;
			continue ;
		}
		content = ls_get_dir_content(ls, dirs);
		if (cli_or_recurse == RECURSE)
			ft_printf("\n%s:\n", dirs->fullpath);
		if (cli_or_recurse == CLI && ls->operands > 1)
			ft_printf("%s:\n", dirs->fullpath);
		if (ls->sort_type != NO_SORT)
			content = ls_sort(content, ls->sort_type, ls->options & OPT_R);
		ls_display(ls, content, DIRECTORY);
		if (content && ls->options & OPT_CAPR)
			ls_dirs(ls, content, RECURSE);
		ls_free_paths(content);
		(dirs = dirs->next) && cli_or_recurse == CLI ? ft_printf("\n") : 0;
	}
}
