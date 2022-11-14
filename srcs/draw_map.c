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

void	drawline(t_data **data, float dx, float dy)
{
	float		steps;
	float	x;
	float	y;
	float	i;

	i = 0;
	x = (*data)->player->x;
	y = (*data)->player->y;
	if (fabsf(dx) > fabsf(dy))
		steps = fabsf(dx);
	else
		steps = fabsf(dy);
	while (i <= steps)
	{
		my_mlx_pixel_put((*data)->img, x, y, create_rgb(218, 0, 55));
		x += dx / steps;
		y += dy / steps;
		i++;
	}
}


void draw_background(t_data **data, unsigned long floor_color, unsigned long ceiling_color)
{
	int x;
	int y;

	y =  -1;
	while(++y < (WINDOW_HEIGHT/2))
	{
		x = -1;
		while(++x < WINDOW_WIDTH)
			my_mlx_pixel_put((*data)->img, x, y, ceiling_color);
	}
	while(++y < (WINDOW_HEIGHT))
	{
		x = -1;
		while(++x < WINDOW_WIDTH)
			my_mlx_pixel_put((*data)->img, x, y, floor_color);
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
		my_mlx_pixel_put((*data)->img, (*data)->player->x + x, (*data)->player->y + y, create_rgb(0, 0, 0));
		angle += 0.01f;
	}
	drawline(data, cos((*data)->player->initialAngle) * 10, sin((*data)->player->initialAngle) * 10);

}

void	draw_minimap(t_data **data)
{
	int		x;
	int		y;
	int		j;

	y = 0;
	j = 0;
	// draw_wall(data);
	while ((*data)->MapDisplay->map[j])
	{
		x = 0;
		while ((*data)->MapDisplay->map[j][x /MINIMAP_TILE_SIZE])
		{
			if (is_valid_char((*data)->MapDisplay->map[j][x / MINIMAP_TILE_SIZE]))
				draw_square(data, x, y, 0xF5EFE6);
			// if((*data)->MapDisplay->map[j][x / MINIMAP_TILE_SIZE] == '1')
			// 	draw_square(data, x, y, 0xc06b31);
			x += MINIMAP_TILE_SIZE;
		}
		y += MINIMAP_TILE_SIZE;
		j++;
	}
}

// pseudo code to draw walls

// wall top y = (window heigth/2) - (wall strip heigth/2)
// wall top y = walltopy < 0 ? 0 : walltop y

// wallbottomy = (window height/2) + (wall strip heigth/2)
//wall bottom y = wallbottomy > windowheight ? window height : wall bottom y
