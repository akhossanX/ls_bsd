/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 11:29:11 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/15 13:13:34 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_putnchar_fd(int fd, int c, int n)
{
	int		i;

	if (fd < 0)
		return (0);
	i = n;
	while (i--)
		ft_putchar_fd(fd, c);
	return (n);
}
