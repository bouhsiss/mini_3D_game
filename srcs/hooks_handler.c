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

// bool	check_wall_collision(t_data **data, t_player **player)
// {
// 	int		i;
// 	int		j;
// 	char	**map;

// 	map = (*data)->MapDisplay->map;
// 	i = ((*player)->x + (cos((*player)->initialAngle + (*player)->sideAngle * \
// 		DEGREE) * ((*player)->walkDirection * (((*player)->moveSpeed))))) \
// 		/ RESOLUTION;
// 	j = ((*player)->y + (sin((*player)->initialAngle + (*player)->sideAngle * \
// 		DEGREE) * ((*player)->walkDirection * (((*player)->moveSpeed))))) \
// 		/ RESOLUTION;
// 	if (map[j][i] != '1' && map[j][i] != ' ')
// 		return(false);
// 	else
// 		return(true);
// }

bool	check_is_wall(t_data **data, int next_x, int next_y)
{
	int		i;
	int		j;
	char	**map;

	map = (*data)->MapDisplay->map;
	i = next_x / RESOLUTION;
	j = next_y / RESOLUTION;
	if (map[j][i] != '1' && map[j][i] != ' ')
	{
		return(false);
	}
	else
		return(true);
}

void update_player_pos(t_data **data, t_player **player)
{
	int next_x;
	int next_y;

	next_x = ((*player)->x + (cos((*player)->initialAngle + (*player)->sideAngle * \
		DEGREE) * ((*player)->walkDirection * (((*player)->moveSpeed)))));
	next_y = ((*player)->y + (sin((*player)->initialAngle + (*player)->sideAngle * \
		DEGREE) * ((*player)->walkDirection * (((*player)->moveSpeed)))));
	if(check_is_wall(data, next_x, next_y) == false)
		update(data);
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
	draw_fov(data, RESOLUTION);
	draw_player(data);
	mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win->mlx_win, \
	(*data)->img->img, 0, 0);
	return (0);
}
