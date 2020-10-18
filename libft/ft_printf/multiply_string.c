/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouras <aybouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 17:39:19 by aybouras          #+#    #+#             */
/*   Updated: 2019/11/24 19:42:20 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	multiply_string function helper
*/

void	ft_multiply(char *res, char *num1, char *num2, t_vars *var)
{
	int k;
	int carry;
	int i;
	int j;
	int sum;

	i = var->len2;
	while (--i >= 0)
	{
		k = var->len - (var->len2 - i);
		carry = 0;
		j = var->len1;
		while (--j >= 0)
		{
			sum = ((num2[i] - '0') * (num1[j] - '0')) + carry + (res[k] - '0');
			carry = sum / 10;
			sum = sum % 10;
			res[k] = (sum + '0');
			k--;
		}
		if (carry > 0)
			res[k] = (carry + '0');
	}
}

/*
**	Performs string multiplication using the old fashioned school way
**	to multiply two numbers returns an allocated string result.
*/

char	*multiply_string(char *num1, char *num2, int c)
{
	int		i;
	char	*res;
	t_vars	var;

	var.len1 = ft_strlen(num1);
	var.len2 = ft_strlen(num2);
	var.len = var.len1 + var.len2 + 1;
	res = (char *)ft_memalloc(sizeof(char) * var.len);
	res[var.len-- - 1] = 0;
	ft_memset(res, '0', var.len);
	ft_multiply(res, num1, num2, &var);
	i = 0;
	while (res[i] && res[i] == '0')
		i++;
	ft_strdel(&num1);
	num1 = ft_strdup(res);
	ft_strdel(&res);
	res = ft_strdup(num1 + i);
	ft_strdel(&num1);
	if (c)
		ft_strdel(&num2);
	return (res);
}
