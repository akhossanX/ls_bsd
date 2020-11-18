
#include "libft.h"

int     ft_ceil(double nb)
{
    if (nb > (double)((int)nb))
        return ((int)(nb + 1));
    return ((int)nb);
}