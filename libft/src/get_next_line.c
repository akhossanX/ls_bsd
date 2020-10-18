
#include "libft.h"

static int	save_line(char **rest, char **line, char *endl)
{
	char	*tmp;

	if (endl)
	{
		tmp = *rest;		
		*line = ft_strsub(*rest, 0, endl - *rest + 1);
		*rest = ft_strdup(endl + 1);
		free(tmp);
		return (1);
	}
	else if (**rest)
	{
		*line = ft_strdup(*rest);
		ft_strdel(rest);
		return (1);
	}
	free(*rest);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*rest[FD_MAX];
	char		*buff;
	int			r;
	char		*e;

	if (fd < 0 || line == NULL || FD_MAX > 4096)
		return (-1);	
	if (!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (!(rest[fd]) && !(rest[fd] = ft_strnew(0)))
	{
		ft_strdel(&buff);
		return (-1);
	}
	while (!(e = ft_strchr(rest[fd], 10)) && (r = read(fd, buff, BUFF_SIZE)) > 0)
	{
		e = rest[fd];
		rest[fd] = ft_strjoin(rest[fd], buff);	
		ft_strdel(&e);
	}
	ft_strdel(&buff);
	return (r < 0 ? -1 : save_line(&rest[fd], line, e));
}
