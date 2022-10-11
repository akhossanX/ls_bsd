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

void	set_wincolumns(t_ls *ls)
{
    struct winsize  w;

    errno = 0;
    ls->fd = 1;//open("/dev/ttys001", O_WRONLY);
    if (ioctl(ls->fd, TIOCGWINSZ, &w) == -1)
    {
        ls->err = errno;
        ls_handle_error(ls, NULL, LS_MAJOR_ERROR);
    }
	ls->display.wincolumns = w.ws_col;
}

void	set_block_data(t_ls *ls, t_path *entry, int *max, int *total_entries)
{
	int	len;

	if (ls->options & OPT_CAPC)
	{
		len = ft_strlen(entry->name);
		if (*max < len)
			*max = len;
		*total_entries += 1;
    	set_wincolumns(ls);
	}
}

void	add_entry_by_type(t_ls *ls, t_path *entry)
{
	t_path	**target;

	target = &ls->files;
	if ((ls->options & OPT_D) == 0 && (entry->st->st_mode & S_IFMT) == S_IFDIR)
			target = &ls->dirs;
	if (target == &ls->files)
		set_block_data(ls, entry, &ls->display.max_files_names, &ls->display.total_files);
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

int32_t	get_minor_major(t_path *entry)
{
	dev_t	st_rdev;

	st_rdev = entry->st->st_rdev;
	entry->major = st_rdev >> 24;
	entry->minor = st_rdev & 0xff;
	return (entry->major > entry->minor ? entry->major : entry->minor);
}

void	set_owner_length(t_ls *ls, t_path *entry)
{
	int		owner_len;

	errno = 0;
	if (!(entry->usrinfo = getpwuid(entry->st->st_uid)) || 
		!(entry->usrname = ft_strdup(entry->usrinfo->pw_name)))
	{
		if (errno && (ls->err = errno))
			ls_handle_error(ls, entry->name, get_error_level(ls->err));
	}
	if (entry->usrinfo == NULL)
	{
		if (!(entry->usrname = ft_ltoa(entry->st->st_uid)))
		{
			ls->err = errno;
			ls_handle_error(ls, entry->name, get_error_level(ls->err));
		}
	}
	owner_len = ft_strlen(entry->usrname);
	if (ls->display.owner_length < owner_len)
		ls->display.owner_length = owner_len;
}

void	set_group_length(t_ls *ls, t_path *entry)
{
	int		grp_len;

	errno = 0;
	if (!(entry->grpinfo = getgrgid(entry->st->st_gid)) ||
		!(entry->grpname = ft_strdup(entry->grpinfo->gr_name)))
	{
		if (errno && (ls->err = errno))
			ls_handle_error(ls, entry->name, get_error_level(ls->err));
	}
	if (entry->grpinfo == NULL)
	{
		if (!(entry->grpname = ft_ltoa(entry->st->st_gid)))
		{
			ls->err = errno;
			ls_handle_error(ls, entry->name, get_error_level(ls->err));
		}
	}
	grp_len = ft_strlen(entry->grpname);
	if (ls->display.grp_length < grp_len)
		ls->display.grp_length = grp_len;
}

void	set_display_data(t_ls *ls, t_path *entry)
{
	int		lnk_len;
	int		size_len;

	ls->display.blocks += entry->st->st_blocks;
	lnk_len = nb_length(entry->st->st_nlink);
	ls->display.lnk_length < lnk_len ? 
		ls->display.lnk_length = lnk_len : 0;
	ls->options & OPT_G ? 0 : set_owner_length(ls, entry);
	set_group_length(ls, entry);
	// SIZE OR MINOR-MAJOR
	if ((entry->st->st_mode & S_IFMT) == S_IFBLK 
		|| (entry->st->st_mode & S_IFMT) == S_IFCHR)
	{
		size_len = nb_length(get_minor_major(entry));
		ls->display.has_cbdev = 1;
	}
	else
		size_len = nb_length(entry->st->st_size);
	ls->display.size_length < size_len ?
		ls->display.size_length = size_len : 0;
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
	if ((ls->options & OPT_L) || (ls->options & OPT_G))
		set_display_data(ls, entry);
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
		ptr->next = NULL;
		if (set_stat(ls, ptr))
			add_entry_by_type(ls, ptr);
		else
			ls_free_paths(ptr);
		ptr = next;
	}
	ls->all = NULL;
}
