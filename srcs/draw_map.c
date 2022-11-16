/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:00:45 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/01 17:37:31 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	drawline(t_data **data, float dx, float dy)
{
	float	steps;
	float	x;
	float	y;
	float	i;

	i = 0;
	x = (*data)->player->x / MINIMAP_COEFF;
	y = (*data)->player->y / MINIMAP_COEFF;
	if (fabsf(dx) > fabsf(dy))
		steps = fabsf(dx);
	else
		steps = fabsf(dy);
	while (i <= steps)
	{
		my_mlx_pixel_put((*data)->win->win_img, x, y, create_rgb(218, 0, 55));
		x += dx / steps;
		y += dy / steps;
		i++;
	}
}

void	draw_background(t_data **data)
{
	int			x;
	int			y;
	t_colors	*c_color;
	t_colors	*f_color;

	c_color = (*data)->mapdisplay->ceiling_color;
	f_color = (*data)->mapdisplay->floor_color;
	y = -1;
	while (++y < (WINDOW_HEIGHT / 2))
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			my_mlx_pixel_put((*data)->win->win_img, x, y, \
			create_rgb(c_color->r, c_color->g, c_color->b));
	}
	while (++y < (WINDOW_HEIGHT))
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			my_mlx_pixel_put((*data)->win->win_img, x, y, \
			create_rgb(f_color->r, f_color->g, f_color->b));
	}
}

void	draw_player(t_data **data)
{
	float	angle;
	int		color;
	float	x;
	float	y;

	color = create_rgb(218, 0, 55);
	angle = 0;
	while (angle <= 360)
	{
		x = RADIUS * cos(angle);
		y = RADIUS * sin(angle);
		drawline(data, x, y);
		angle += 0.01f;
	}
	drawline(data, cos((*data)->player->initial_angle) * 10, \
	sin((*data)->player->initial_angle) * 10);
}

void	draw_minimap(t_data **data)
{
	int		x;
	int		y;
	int		j;

	y = 0;
	j = 0;
	while ((*data)->mapdisplay->map[j])
	{
		x = 0;
		while ((*data)->mapdisplay->map[j][x / (TILE_SIZE / MINIMAP_COEFF)])
		{
			if (is_valid_char((*data)->mapdisplay->map[j][x / \
			(TILE_SIZE / MINIMAP_COEFF)]))
				draw_square(data, x, y, 0xF5EFE6);
			x += TILE_SIZE / MINIMAP_COEFF;
		}
		y += TILE_SIZE / MINIMAP_COEFF;
		j++;
	}
}
