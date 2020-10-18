
#include "libft.h"

int		ft_strcasecmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while (p1[i] && ft_tolower(p1[i]) == ft_tolower(p2[i]))
		i++;
	return (ft_tolower(p1[i]) - ft_tolower(p2[i]));
}
