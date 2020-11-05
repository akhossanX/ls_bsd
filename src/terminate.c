
#include "ft_ls.h"

void	free_paths(t_path *lst)
{
	t_path	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	ft_ls_terminate(t_ls *ls, int err)
{
	if (err > 0)
		ft_dprintf(STDERR, "%s: %s\n", ls->prog, strerror(err));
	//free_paths(ls->paths);
	if (ls)
	{
		free_paths(ls->dirs);
		free_paths(ls->files);
		free(ls);
		exit(ls->errcode);	// Need to exit with ls->errcode error
	}
	if (err)
		exit(err);
}
