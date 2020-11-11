/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:16:46 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/07 14:13:21 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long		ls_asciicmp(t_path *p1, t_path *p2, t_sort sort_type)
{
	(void)sort_type;
	return (-ft_strcmp(p1->name, p2->name));
}

long	nbcmp(t_path *p1, t_path *p2, t_sort sort_type)
{
	long	ret;

	ret = 0;
	if (sort_type == ATIME_SORT)
		ret = p1->st->st_atimespec.tv_sec - p2->st->st_atimespec.tv_sec;
	else if (sort_type == MTIME_SORT)
		ret = p1->st->st_mtimespec.tv_sec - p2->st->st_mtimespec.tv_sec;
	else if (sort_type == CTIME_SORT)
		ret = p1->st->st_ctimespec.tv_sec - p2->st->st_ctimespec.tv_sec;
	else if (sort_type == SIZE_SORT)
		ret = p1->st->st_size - p2->st->st_size; // Check the type definition for st_size
	return (ret == 0 ? ls_asciicmp(p1, p2, sort_type) : ret);
}

t_path	*find_middle_list(t_path *lst)
{
	t_path	*middle;
	t_path	*midnext;

	middle = lst;
	midnext = lst;
	while (midnext)
	{
		if (midnext->next)
		{
			midnext = midnext->next;
			if (midnext->next)
			{
				midnext = midnext->next;
				middle = middle->next;
			}
		}
		else
			midnext = midnext->next;
	}
	return (middle);
}

t_path	*merge_list(t_path *left, t_path *rigth, t_cmp cmp_func, t_sort sort_type, int reverse)
{
	t_path	*m;
	t_path	*last;
	long	test;

	if (left == NULL || rigth == NULL)
		return (!left ? rigth : left);
	m = NULL;
	last = NULL;
	while (left && rigth)
	{
		test = cmp_func(left, rigth, sort_type);
		// ft_printf("{%s, %s, %d}\n", left->name, rigth->name, test);
		reverse ? test *= -1 : 0;
		if (test > 0)
		{
			if (m == NULL)
				m = left;
			else
				last->next = left;
			last = left;
			left = left->next;
		}
		else
		{
			if (m == NULL)
				m = rigth;
			else
				last->next = rigth;
			last = rigth;
			rigth = rigth->next;
		}
	}
	last->next = (left == NULL) ? rigth : left;
	return (m);
}

t_path	*merge_sort(t_path *lst, t_cmp cmp_func, t_sort sort_type, int reverse)
{
	t_path	*middle;
	t_path	*midnext;
	t_path	*left;
	t_path	*rigth;

	if (lst == NULL || lst->next == NULL)
		return (lst);	
	middle = find_middle_list(lst);	
	midnext = middle->next;
	middle->next = NULL;
	left = merge_sort(lst, cmp_func, sort_type, reverse);
	rigth = merge_sort(midnext, cmp_func, sort_type, reverse);
	return (merge_list(left, rigth, cmp_func, sort_type, reverse));
}


t_cmp	ls_get_cmp_func(t_sort sort_type)
{
	if (sort_type == ASCII_SORT)
		return (ls_asciicmp);
	return (nbcmp);
}

void	ls_sort(t_path **target, t_sort sort_type, int reverse)
{
	t_cmp	cmp_func;

	cmp_func = ls_get_cmp_func(sort_type); // Gets the function that handles the comparison
	*target = merge_sort(*target, cmp_func, sort_type, reverse);
	
}
