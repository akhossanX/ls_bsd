/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 11:56:41 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/08 12:50:27 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_error_level(int error)
{
	if (error == ENOMEM || error == EMFILE || error == ENFILE)
		return (LS_MAJOR_ERROR);
	return (error == 0 ? LS_SUCCESS : LS_MINOR_ERROR);
}

void	ls_handle_error(t_ls *ls, const char *arg, int error_level)
{
	if (error_level == LS_MAJOR_ERROR)
	{
		ft_dprintf(STDERR, "%s: %s\n", ls->prog, strerror(ls->errcode));
		ls_clean_all(ls);
		exit(LS_MAJOR_ERROR);
	}
	else
	{
		ft_dprintf(STDERR, "%s: %s: %s\n", 
			ls->prog, arg, strerror(ls->errcode));
	}
}
