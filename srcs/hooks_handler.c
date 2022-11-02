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
// 	(*data)->player->x = (cos((*data)->player->initialAngle + \
// 		(*data)->player->sideAngle * DEGREE) * ((*data)->player->walkDirection \
// 		* ((*data)->player->moveSpeed)));
// 	(*data)->player->y = (sin((*data)->player->initialAngle + \
// 		(*data)->player->sideAngle * DEGREE) * ((*data)->player->walkDirection \
// 		* ((*data)->player->moveSpeed)));
	(*data)->player->x = next_x;
	(*data)->player->y = next_y;
}

bool	check_is_wall(t_data **data, float next_x, float next_y)
{
	int		i;
	int		j;
	char	**map;

	map = (*data)->MapDisplay->map;
	i = next_x / TILE_SIZE;
	j = next_y / TILE_SIZE;
	if (map[j][i] != '1' && map[j][i] != ' ')
	{
		return (false);
	}
	else
		return (true);
}

void	update_player_pos(t_data **data, t_player **player)
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

int	handler(t_data **data)
{
	mlx_hook((*data)->win->mlx_win, 17, 1L << 5, close_win, (*data));
	mlx_hook((*data)->win->mlx_win, 02, 1L << 0, move_player, data);
	mlx_hook((*data)->win->mlx_win, 03, 1L << 1, keyrelease, data);
	(*data)->player->initialAngle += (*data)->player->turnDirection * \
		(*data)->player->rotationSpeed;
	update_player_pos(data, &(*data)->player);
	draw_mini_map(data);
	cast_rays(data);
	draw_player(data);
	render_walls(data);
	mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win->mlx_win, \
	(*data)->img->img, 0, 0);
	return (0);
}
