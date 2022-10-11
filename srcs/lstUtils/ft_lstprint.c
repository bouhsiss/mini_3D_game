#include "cub3D.h"


void ft_lstprint(t_lst **list)
{
	t_lst *tmp;

	tmp = (*list);
	while(tmp)
	{
		printf("%s", tmp->content);
		tmp = tmp->next;
	}
}