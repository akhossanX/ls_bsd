
#include "ft_ls.h"

t_path	*ft_ls_path_new(t_ls *ls, const char *path)
{
	t_path	*node;

	if (!(node = (t_path *)ft_memalloc(sizeof(t_path))))
		ft_ls_terminate(ls, errno);
	//if (!(node->name = ft_strdup(path)))
		//ft_ls_terminate(ls, errno);
	ft_strncpy(node->name, path, MAX_PATH_LEN);
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
		{
			ls->errcode < 2 ? ls->errcode = 2 : 0;
			ft_dprintf(STDERR, "%s: %s: %s\n", ls->prog, arg, strerror(errno));
			return ;
		}
	}
	else
		ls->dir_count++;	
	closedir(dp);
	if (!(path = ft_ls_path_new(ls, arg)))
		ft_ls_terminate(ls, errno);
	ft_ls_path_add(target, path);
}

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
