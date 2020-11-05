
#include "ft_ls.h"

t_path	*ft_ls_path_new(t_ls *ls, const char *parent, const char *path)
{
	t_path	*node;

	errno = 0;
	if (!(node = (t_path *)ft_memalloc(sizeof(t_path))))
	{
		ls->errcode = errno;
		return (NULL);
	}
	ft_strncpy(node->name, path, MAX_PATH_LEN);
	if (parent)
		ft_strncpy(node->parent, parent, MAX_PATH_LEN);
	return (node);
}

void	ft_ls_path_add(t_path **lst, t_path *new)
{
	t_path	*ptr;

	if (!*lst)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;	
		ptr->next = new;
	}
}

void	ft_ls_get_path(t_ls *ls, char *arg)
{
	t_path	*path;
	DIR		*dp;
	t_path	**target;

	target = &ls->dirs;
	errno = 0;
	dp = ft_strequ(arg, ".") ? NULL : opendir(arg);
	if (errno)
	{
		if (errno == ENOTDIR)
			target = &ls->files;
		else
			return ;
	}
	else
		ls->dir_count++;
	dp ? closedir(dp) : 0;
	if (!(path = ft_ls_path_new(ls, NULL, arg)))
		ft_ls_terminate(ls, errno);//should free everything
	ft_ls_path_add(target, path);
}

int		ft_ls_get_path(t_ls *ls, char *arg)
{
	errno = 0;
	ls->dp = opendir(arg);	
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
