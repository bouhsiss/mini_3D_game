#include "cub3D.h"

void ft_lstdelete(t_lst **lst)
{
	t_lst *tmp;

	while((*lst))
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp->content);
		free(tmp);
	}
}