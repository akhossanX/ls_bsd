
#include "libft.h"

int			nb_length(long long nb)
{
	size_t	i;

	i = 1;
	while (nb / 10 != 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}