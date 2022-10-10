#include "cub3D.h"

void freeArray(char **arr)
{
	int i;

	i = -1;
	while(arr[++i])
		free(arr[i]);
	free(arr);
}