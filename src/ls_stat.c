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
//TODO: This function should be added to libft
int		nb_length(int nb)
{
	int		len;

	len = 1;
	while (nb / 10)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

int32_t	get_minor_major(t_path *entry)
{
	dev_t	st_rdev;

	st_rdev = entry->st->st_rdev;
	entry->major = st_rdev >> 24;
	entry->minor = st_rdev & 0xff;
	return (entry->major > entry->minor ? entry->major : entry->minor);
}

void	set_display_data(t_ls *ls, t_path *entry)
{
	int		lnk_len;
	int		owner_len;
	int		grp_len;
	int		size_len;

	if (ls->options & OPT_L)
	{
		ls->display.blocks += entry->st->st_blocks;
		lnk_len = nb_length(entry->st->st_nlink);
		ls->display.lnk_length < lnk_len ? 
			ls->display.lnk_length = lnk_len : 0;
		errno = 0;
		entry->usrinfo = getpwuid(entry->st->st_uid);
		entry->usrname = ft_strdup(entry->usrinfo->pw_name);
		owner_len = ft_strlen(entry->usrname); 
		ls->display.owner_length < owner_len ?
			ls->display.owner_length = owner_len : 0;
		entry->grpinfo = getgrgid(entry->st->st_gid);
		entry->grpname = ft_strdup(entry->grpinfo->gr_name);
		grp_len = ft_strlen(entry->grpname); // Owner's group length
		ls->display.grp_length < grp_len ? 
			ls->display.grp_length = grp_len : 0;
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