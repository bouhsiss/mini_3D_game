#include "cub3D.h"

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*list;

	list = *lst;
	if (!new)
		return ;
	new->next = NULL;
	if (!*lst)
	{
		new->previous = NULL;
		*lst = new;
	}
	else
	{
		list = ft_lstlast(*lst);
		list->next = new;
		new->previous = list;
	}
}