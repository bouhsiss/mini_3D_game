/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:00:59 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:01:02 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update(t_data **data, float next_x, float next_y)
{
	(*data)->player->x = next_x;
	(*data)->player->y = next_y;
}

bool	check_is_wall(t_data **data, float next_x, float next_y)
{
	int		i;
	int		j;
	char	**map;

	map = (*data)->MapDisplay->map;
	i = next_x / MINIMAP_TILE_SIZE;
	j = next_y / MINIMAP_TILE_SIZE;
	if (map[j][i] != '1' && map[j][i] != ' ')
	{
		return (false);
	}
	else
		return (true);
}

void	move_player(t_data **data, t_player **player)
{
	float	next_x;
	float	next_y;

	next_x = ((*player)->x + (cos((*player)->initialAngle + \
		(*player)->sideAngle * DEGREE) * ((*player)->walkDirection * \
		(((*player)->moveSpeed)))));
	next_y = ((*player)->y + (sin((*player)->initialAngle + \
		(*player)->sideAngle * DEGREE) * ((*player)->walkDirection * \
		(((*player)->moveSpeed)))));
	if(check_is_wall(data, next_x, (*player)->y) == false)
		update(data, next_x, (*player)->y);
	if(check_is_wall(data, (*player)->x, next_y) == false)
		update(data, (*player)->x, next_y);
	
}