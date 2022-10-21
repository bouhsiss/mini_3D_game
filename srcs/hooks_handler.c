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

void	update(t_data **data)
{
	(*data)->player->x += (cos((*data)->player->initialAngle + \
		(*data)->player->sideAngle * DEGREE) * ((*data)->player->walkDirection \
		* ((*data)->player->moveSpeed)));
	(*data)->player->y += (sin((*data)->player->initialAngle + \
		(*data)->player->sideAngle * DEGREE) * ((*data)->player->walkDirection \
		* ((*data)->player->moveSpeed)));
}

void	check_wall_collision(t_data **data, t_player **player)
{
	int		i;
	int		j;
	char	**map;

	map = (*data)->MapDisplay->map;
	i = ((*player)->x + (cos((*player)->initialAngle + (*player)->sideAngle * \
		DEGREE) * ((*player)->walkDirection * (((*player)->moveSpeed))))) \
		/ RESOLUTION;
	j = ((*player)->y + (sin((*player)->initialAngle + (*player)->sideAngle * \
		DEGREE) * ((*player)->walkDirection * (((*player)->moveSpeed))))) \
		/ RESOLUTION;
	if (map[j][i] != '1' && map[j][i] != ' ')
		update(data);
}

int	handler(t_data **data)
{
	mlx_hook((*data)->win->mlx_win, 17, 1L << 5, close_win, (*data));
	mlx_hook((*data)->win->mlx_win, 02, 1L << 0, move_player, data);
	mlx_hook((*data)->win->mlx_win, 03, 1L << 1, keyrelease, data);
	(*data)->player->initialAngle += (*data)->player->turnDirection * \
		(*data)->player->rotationSpeed;
	check_wall_collision(data, &(*data)->player);
	draw_mini_map(data);
	return (0);
}
