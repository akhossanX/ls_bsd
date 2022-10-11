/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:19:14 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/08 12:33:34 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path	*ls_path_new(t_ls *ls, const char *parent, const char *name)
{
	t_path	*node;

	errno = 0;
	if (!(node = (t_path *)ft_memalloc(sizeof(t_path))) && 
			(ls->err = errno))
		ls_handle_error(ls, NULL, LS_MAJOR_ERROR);
	if (!(node->name = ft_strdup(name)) && (ls->err = errno))
	{
		free(node);
		ls_handle_error(ls, NULL, LS_MAJOR_ERROR);
	}
	if (!parent)
 		node->fullpath = ft_strdup(name);
	else
		node->fullpath = get_full_path(parent, name);
	if (errno)
	{
		ls->err = errno;
		ft_strdel(&node->name);
		ft_strdel(&node->fullpath);
		free(node);
		ls_handle_error(ls, NULL, LS_MAJOR_ERROR);
	}
	return (node);
}

void	ls_path_append(t_path **lst, t_path *new)
{
	t_path	*ptr;

	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_path	*ls_save_path(t_ls *ls, t_path **target_list, const char *parent, 
		const char *name)
{
	t_path	*new;

	new = ls_path_new(ls, parent, name);
	ls_path_append(target_list, new);
	return (new);
}
