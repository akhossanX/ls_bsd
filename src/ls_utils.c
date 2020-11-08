/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 09:56:30 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/08 11:34:39 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

char    *get_full_path(const char *parent, const char *entry)
{
    char    *fullpath;
    char    *tmp;

    errno = 0;
    if (!parent)
        return (ft_strdup(entry));
	if (parent[ft_strlen(parent) - 1] != '/')
	{
    	if (!(tmp = ft_strjoin(parent, "/")))
        	return (NULL);
		fullpath = ft_strjoin(tmp, entry);
		ft_strdel(&tmp);
	}
	else
    	fullpath = ft_strjoin(parent, entry);
    return (fullpath);
}
