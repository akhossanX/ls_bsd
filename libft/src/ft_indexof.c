/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:58:09 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/08 11:57:00 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Finds the index of a given character
**	in a C proper string.
**	Returns -1 if the character is not found
**	inside the string.
*/

int		ft_indexof(char *s, char c)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}
