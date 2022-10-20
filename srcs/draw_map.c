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

void	drawline(t_data **data, int dx, int dy)
{
	int		steps;
	float	x;
	float	y;
	int		i;

	i = 0;
	x = (*data)->player->x;
	y = (*data)->player->y;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	while (i <= steps)
	{
		my_mlx_pixel_put((*data)->img, x, y, create_rgb(218, 0, 55));
		x += dx / (float)steps;
		y += dy / (float)steps;
		i++;
	}
}

void	draw_player(t_data **data)
{
	double	angle;
	int		color;
	double	x;
	double	y;

	color = create_rgb(218, 0, 55);
	angle = 0;
	while (angle <= 360)
	{
		x = RADIUS * cos(angle);
		y = RADIUS * sin(angle);
		drawline(data, x, y);
		angle += 0.01f;
	}
	drawline(data, ((RESOLUTION) * cos((*data)->player->initialAngle)), \
	((RESOLUTION) * sin((*data)->player->initialAngle)));
}

void	draw_mini_map(t_data **data, t_lst **map, char *line)
{
	int		x;
	int		y;
	t_lst	*tmp;

	y = 0;
	tmp = (*map);
	draw_wall(data);
	while (tmp)
	{
		x = 0;
		line = tmp->content;
		while (line[x / RESOLUTION])
		{
			if (is_valid_char(line[x / RESOLUTION]))
				put_square_in_image(data, x, y, create_rgb(115, 113, 113));
			x += RESOLUTION;
		}
		y += RESOLUTION;
		tmp = tmp->next;
	}
	draw_player(data);
	mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win->mlx_win, \
	(*data)->img->img, 0, 0);
}

void	draw_map(t_data **data)
{
	(*data)->mlx_ptr = mlx_init();
	(*data)->win->mlx_win = mlx_new_window((*data)->mlx_ptr, \
		(*data)->MapDisplay->NbrOfColumns * RESOLUTION, \
		(*data)->MapDisplay->NbrOfRows * RESOLUTION, "SmolWolf3D");
	(*data)->img->img = mlx_new_image((*data)->mlx_ptr, \
		RESOLUTION * (*data)->MapDisplay->NbrOfColumns, \
		RESOLUTION * (*data)->MapDisplay->NbrOfRows);
	(*data)->img->addr = mlx_get_data_addr((*data)->img->img, \
		&((*data)->img->bits_per_pixel), &((*data)->img->line_length), \
		&((*data)->img->endian));
	draw_mini_map(data, &(*data)->MapDisplay->map, \
		(*data)->MapDisplay->map->content);
	mlx_loop_hook((*data)->mlx_ptr, handler, data);
	mlx_loop((*data)->mlx_ptr);
}
