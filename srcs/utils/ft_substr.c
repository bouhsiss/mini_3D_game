#include "cub3D.h"


char	*ft_substr(char *s, int start, int len)
{
	char			*substr;
	int 		size;
	int 		i;

	size = len;
	if (!(s))
		return (NULL);
	if (start >= ft_strlen(s) || s[0] == '\0')
		return (NULL);
	if (len > ft_strlen(s))
		size = ft_strlen(s) - start;
	substr = (char *)malloc(size * sizeof(char) + 1);
	if (!(substr))
		return (0);
	i = 0;
	while (i < size)
	{
		substr[i] = (char)s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}