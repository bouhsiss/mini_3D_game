/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:22:35 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/01 00:52:46 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

unsigned int	create_rgb(int r, int g, int b)
{
	return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + ((b & 0xFF)));
}

unsigned int my_mlx_pixel_get(t_img *img, int x, int y)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	char *src = img->addr + (y * img->line_length) + x * (img->bits_per_pixel / 8);
	return(*(unsigned int *)src);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_data **data, int x, int y, unsigned long color)
{
	int	i;
	int	j;
	int	tmp_x;

	i = 0;
	tmp_x = x;
	while (++i < TILE_SIZE/MINIMAP_COEFF)
	{
		x = tmp_x;
		j = 0;
		while (++j < TILE_SIZE/MINIMAP_COEFF)
		{
			my_mlx_pixel_put((*data)->win->win_img, x, y, color);
			x++;
		}
		y++;
	}
}
