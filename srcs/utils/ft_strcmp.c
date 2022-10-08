#include "cub3D.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t				i;

	i = 0;
	if(!s1 || !s2)
		return(-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}