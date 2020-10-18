
#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(dst);
	i = 0;
	while (src[i] && i < n)
	{
		dst[i + j] = src[i];
		i++;
	}
	dst[i + j] = '\0';
	return (dst);
}
