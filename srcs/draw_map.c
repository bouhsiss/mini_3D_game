/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:00:45 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:00:48 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
create_rgb(23, 23, 23); // wall
create_rgb(115, 113, 113); //floor
create_rgb(218, 0, 55); // player
*/

/* MATRIX PALETTE
create_rgb(54, 189, 0); //wall
create_rgb(0, 0, 0); // floor
create_rgb(255, 255, 255);
*/

void	draw_wall(t_data **data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < MINI_MAP_TILE_SIZE * (*data)->MapDisplay->NbrOfRows)
	{
		x = -1;
		while (++x < MINI_MAP_TILE_SIZE * (*data)->MapDisplay->NbrOfColumns)
			my_mlx_pixel_put((*data)->img, x, y, 0x808080);
	}
}


void	draw_player(t_data **data)
{
	float	angle;
	int		color;
	float	x;
	float	y;

	color = create_rgb(255, 122, 78);
	angle = 0;
	while (angle <= 2*PI)
	{
		x = (RADIUS * cos(angle));
		y = (RADIUS * sin(angle));
		drawline(data, x, y, color);
		angle += 0.0001f;
	}
}

void	draw_mini_map(t_data **data)
{
	int		x;
	int		y;
	int		j;

	y = 0;
	j = 0;
	draw_wall(data);
	while ((*data)->MapDisplay->map[j])
	{
		x = 0;
		while ((*data)->MapDisplay->map[j][x / MINI_MAP_TILE_SIZE])
		{
			if (is_valid_char((*data)->MapDisplay->map[j][x / MINI_MAP_TILE_SIZE]))
				draw_square(data, x, y, create_rgb(0, 0, 0));
			else if((*data)->MapDisplay->map[j][x / MINI_MAP_TILE_SIZE] == '1')
				draw_square(data, x, y, create_rgb(255, 255, 255));
			x += MINI_MAP_TILE_SIZE;
		}
		y += MINI_MAP_TILE_SIZE;
		j++;
	}
}
