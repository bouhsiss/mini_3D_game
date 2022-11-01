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
	while (++y < RESOLUTION * (*data)->MapDisplay->NbrOfRows)
	{
		x = -1;
		while (++x < RESOLUTION * (*data)->MapDisplay->NbrOfColumns)
			my_mlx_pixel_put((*data)->img, x, y, create_rgb(23, 23, 23));
	}
}

void	drawline(t_data **data, int dx, int dy, unsigned long color)
{
	int		steps;
	float	x;
	float	y;
	float	i;

	i = 0;
	x = (*data)->player->x;
	y = (*data)->player->y;
	if (abs(dx) > abs(dy))
		steps = abs(dx)*10;
	else
		steps = abs(dy)*10;
	while (i <= steps)
	{
		my_mlx_pixel_put((*data)->img, x, y, color);
		x += dx / (float)steps;
		y += dy / (float)steps;
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
	while (angle <= 360)
	{
		x = (RADIUS * cos(angle));
		y = (RADIUS * sin(angle));
		drawline(data, x, y, color);
		angle += 0.01f;
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
		while ((*data)->MapDisplay->map[j][x / RESOLUTION])
		{
			if (is_valid_char((*data)->MapDisplay->map[j][x / RESOLUTION]))
				put_square_in_image(data, x, y, create_rgb(115, 113, 113));
			x += RESOLUTION;
		}
		y += RESOLUTION;
		j++;
	}
}

void	draw_map(t_data **data)
{
	(*data)->mlx_ptr = mlx_init();
	// (*data)->win->mlx_win = mlx_new_window((*data)->mlx_ptr, \
	// 	(*data)->MapDisplay->NbrOfColumns * RESOLUTION, \
	// 	(*data)->MapDisplay->NbrOfRows * RESOLUTION, "SmolWolf3D");
	(*data)->win->mlx_win = mlx_new_window((*data)->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT, "SmolWolf3D");
	// (*data)->img->img = mlx_new_image((*data)->mlx_ptr, \
	// 	RESOLUTION * (*data)->MapDisplay->NbrOfColumns, \
	// 	RESOLUTION * (*data)->MapDisplay->NbrOfRows);
	(*data)->img->img = mlx_new_image((*data)->mlx_ptr,WINDOW_WIDTH, WINDOW_HEIGHT);
	(*data)->img->addr = mlx_get_data_addr((*data)->img->img, \
		&((*data)->img->bits_per_pixel), &((*data)->img->line_length), \
		&((*data)->img->endian));
	mlx_loop_hook((*data)->mlx_ptr, handler, data);
	mlx_loop((*data)->mlx_ptr);
}
