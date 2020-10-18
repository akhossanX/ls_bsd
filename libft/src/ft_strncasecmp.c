
#include "libft.h"

int		ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && (unsigned)ft_tolower(s1[i]) == (unsigned)ft_tolower(s2[i]))
		i++;
	return ((unsigned)ft_tolower(s1[i]) - (unsigned)ft_tolower(s2[i]));
}
