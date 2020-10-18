
#include "libft.h"

int		ft_isnumeric(const char *s)
{
	int		i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (s[i])
	{
		while (s[i])
		{
			if (!ft_isdigit(s[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
