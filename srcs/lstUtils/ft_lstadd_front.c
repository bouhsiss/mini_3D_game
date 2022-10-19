/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:02:19 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:02:22 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_lstadd_front(t_lst **lst, t_lst *new)
{
	if (!new)
		return ;
	new->next = *lst;
	new->previous = NULL;
	if((*lst) != NULL)
		(*lst)->previous = new;
	*lst = new;
}
