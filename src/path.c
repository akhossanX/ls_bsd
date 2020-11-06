/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:19:14 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/06 14:24:26 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path	*ft_ls_path_new(t_ls *ls, const char *parent, const char *name)
{
	t_path	*node;

	errno = 0;
	if (!(node = (t_path *)ft_memalloc(sizeof(t_path))))
	{
		ls->errcode = errno;
		return (NULL);
	}
	if (!(node->name = ft_strdup(path)))
	{
		ls->errcode = errno;
		free(node);
		return (NULL);
	}
	if (parent && !(node->parent = ft_strdup(parent)))
	{
		ls->errcode = errno;
		ft_strdel(&node->name);
		free(node);
		return (NULL);
	}
	return (node);
}

void	ls_save_path(t_ls *ls, t_path **target_list, const char *parent, 
		const char *name)
{
	t_path	*new;
	t_path	*ptr;

	new = ls_path_new(ls, parent, name);	
	if (new == NULL && ls->errcode == ENOMEM)
		ls_handle_error(ls, NULL, LS_MAJOR_ERROR);
	if (*target_list == NULL)
	{
		*target_list = new;
		return ;
	}
	ptr = *target_list;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

/*
**	For debugging
*/

void	print_paths(t_path *lst)
{
	t_path	*p;

	p = lst;
	while (p)
	{
		ft_printf("%s\n", p->name);
		p = p->next;
	}
}
