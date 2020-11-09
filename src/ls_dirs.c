/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:23:53 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/09 10:22:53 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_process_dirs(t_ls *ls, t_path **dirs)
{
	if (ls->sort_type == NO_SORT)
	{
		if (ls->options & OPT_L)
			set_stat(ls, *dirs);
	}
	else
	{
		if ((ls->options & OPT_L) || ls->sort_type != ASCII_SORT)
			set_stat(ls, *dirs);
		ls_sort(ls, dirs);
	}
}

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
	ls_closedir(&ls->dp);
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
    t_path          *content;

    errno = 0;
    if ((ls->dp = opendir(dir->fullpath)))
    {
		content = ls_readdir(ls, dir->fullpath);
		return (content);
    }
	ls->errcode = errno;
	if (errno != ENOTDIR)
		ls_handle_error(ls, dir->name, get_error_level(ls->errcode));
	ls->errcode = 0;
    return (NULL);
}























void	ls_dirs(t_ls *ls, t_path *dirs, int cli_or_recurse)
{
	t_path	*dir_content;

	if (dirs == NULL)
		return ;
	while (dirs != NULL)
	{
		if (cli_or_recurse == RECURSE && 
				(ft_strequ(dirs->name, ".") || ft_strequ(dirs->name, "..")))
		{
			dirs = dirs->next;
			continue ;
		}
		if (!(dir_content = ls_get_dir_content(ls, dirs)) && ls->errcode)
			ls_handle_error(ls, NULL, get_error_level(ls->errcode));
		if (cli_or_recurse == RECURSE && ls_is_dir(ls, dirs->fullpath))
			ft_printf("\n%s:\n", dirs->fullpath);
		if (cli_or_recurse == CLI_DIRS && ls->operands > 1)
			ft_printf("%s:\n");
		ls_process_dirs(ls, &dir_content);
		ls_display(ls, dir_content);
		if (ls->options & OPT_CAPR)
			ls_dirs(ls, dir_content, RECURSE);
		ls_free_paths(dir_content);
		dirs = dirs->next;
	}
}
