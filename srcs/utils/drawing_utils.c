/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:22:35 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/21 11:22:44 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

unsigned long	create_rgb(int r, int g, int b)
{
	return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + ((b & 0xFF)));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(int *)dst = color;
}


void draw_rectangle(t_data **data, int x, int y, float length)
{
	int i;
	int j;
	int tmp_x;
	unsigned long color;

	i = 0;
	tmp_x = x;
	color = 0xbf0001;
	if(length >= WINDOW_HEIGHT)
	{
		length = WINDOW_HEIGHT - 1;
		y = 0;
	}
	while(++i < length)
	{
		x = tmp_x;
		j = 0;
		while(++j <=  RAY_STRIP_WIDTH)
		{
			my_mlx_pixel_put((*data)->img, x+j, y+i, color);
		}
	}
}

void draw_background(t_data **data, unsigned long floor_color, unsigned long ceiling_color)
{
	int x;
	int y;

	y =  -1;
	while(++y < (WINDOW_HEIGHT)/2)
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

void	draw_square(t_data **data, int x, int y, unsigned long color)
{
	int	i;
	int	j;
	int	tmp_x;

	i = 0;
	tmp_x = x;
	while (++i < MINI_MAP_TILE_SIZE)
	{
		x = tmp_x;
		j = 0;
		while (++j < MINI_MAP_TILE_SIZE)
		{
			my_mlx_pixel_put((*data)->img, x, y, color);
			x++;
		}
		y++;
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
