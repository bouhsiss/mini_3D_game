#include "cub3D.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	char		*sorc;
	size_t		i;

	sorc = (char *)src;
	dest = (char *)dst;
	i = 0;
	if (dst != 0 || src != 0)
	{
		while (i < n)
		{
			dest[i] = sorc[i];
			i++;
		}
	}
	return (dst);
}