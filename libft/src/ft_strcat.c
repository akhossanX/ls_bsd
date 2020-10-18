/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:28:38 by aybouras          #+#    #+#             */
/*   Updated: 2019/04/17 13:45:32 by aybouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	size_s1;
	int		j;

	size_s1 = ft_strlen(s1);
	j = 0;
	while (s2[j] != '\0')
	{
		s1[size_s1] = s2[j];
		size_s1++;
		j++;
	}
	s1[size_s1] = '\0';
	return (s1);
}
