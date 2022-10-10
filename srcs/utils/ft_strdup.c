#include "cub3D.h"

static void	*ft_memcpy(void *dst, const void *src, size_t n)
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

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		sz;

	sz = ft_strlen(s1);
	s2 = (char *)malloc(sz * sizeof (char) + 1);
	if (!(s2))
		return (0);
	ft_memcpy(s2, s1, sz);
	s2[sz] = '\0';
	return (s2);
}