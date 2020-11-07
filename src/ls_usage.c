/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:58:43 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/07 11:15:16 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_usage(t_ls *ls, const char option)
{
	ft_dprintf(STDERR, "%s: %s %c\n", ls->prog, "illegal option --", option);
	ft_dprintf(STDERR, "usage: ./ft_ls [%-l1rRatAgGdufcCS] [file ...]\n");
	free(ls);
	exit(1);	
}
