#include "cub3D.h"

void	ft_lstadd_front(t_lst **lst, t_lst *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}