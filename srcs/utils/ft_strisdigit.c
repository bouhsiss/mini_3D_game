#include "cub3D.h"

int ft_strisdigit(char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		if(!(str[i] >= '0' && str[i] <= '9'))
			return(0);
	}
	return(1);
}