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
	while (++y < TILE_SIZE * (*data)->MapDisplay->NbrOfRows)
	{
		x = -1;
		while (++x < TILE_SIZE * (*data)->MapDisplay->NbrOfColumns)
			my_mlx_pixel_put((*data)->img, x, y, create_rgb(23, 23, 23));
	}
}

void	drawline(t_data **data, float dx, float dy, unsigned long color)
{
	float		steps;
	float	x;
	float	y;
	float	i;

	i = 0;
	x = (*data)->player->x;
	y = (*data)->player->y;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	while (i <= steps)
	{
		my_mlx_pixel_put((*data)->img, x, y, color);
		x += dx / steps;
		y += dy / steps;
		i++;
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
		while ((*data)->MapDisplay->map[j][x / TILE_SIZE])
		{
			if (is_valid_char((*data)->MapDisplay->map[j][x / TILE_SIZE]))
				put_square_in_image(data, x, y, create_rgb(115, 113, 113));
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
		j++;
	}
}

void	draw_map(t_data **data)
{
	(*data)->mlx_ptr = mlx_init();
	(*data)->win->mlx_win = mlx_new_window((*data)->mlx_ptr, \
		(*data)->MapDisplay->NbrOfColumns * TILE_SIZE, \
		(*data)->MapDisplay->NbrOfRows * TILE_SIZE, "SmolWolf3D");
	// (*data)->win->mlx_win = mlx_new_window((*data)->mlx_ptr, \
	// 	WINDOW_WIDTH, WINDOW_HEIGHT, "SmolWolf3D");
	(*data)->img->img = mlx_new_image((*data)->mlx_ptr, \
		TILE_SIZE * (*data)->MapDisplay->NbrOfColumns, \
		TILE_SIZE * (*data)->MapDisplay->NbrOfRows);
	// (*data)->img->img = mlx_new_image((*data)->mlx_ptr,WINDOW_WIDTH, WINDOW_HEIGHT);
	(*data)->img->addr = mlx_get_data_addr((*data)->img->img, \
		&((*data)->img->bits_per_pixel), &((*data)->img->line_length), \
		&((*data)->img->endian));
	mlx_loop_hook((*data)->mlx_ptr, handler, data);
	mlx_loop((*data)->mlx_ptr);
}
