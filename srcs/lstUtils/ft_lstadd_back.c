/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:02:13 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:02:14 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
