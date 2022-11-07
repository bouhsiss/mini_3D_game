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

unsigned long	create_rgb(int r, int g, int b)
{
	return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + ((b & 0xFF)));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

 	// if (x < 0 || x > ( * MINIMAP_TILE_SIZE)|| y < 0 || y > ((9)  * MINIMAP_TILE_SIZE))
		// return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_square_in_image(t_data **data, int x, int y, unsigned long color)
{
	int	i;
	int	j;
	int	tmp_x;

	i = 0;
	tmp_x = x;
	while (++i < MINIMAP_TILE_SIZE)
	{
		x = tmp_x;
		j = 0;
		while (++j < MINIMAP_TILE_SIZE)
		{
			my_mlx_pixel_put((*data)->img, x, y, color);
			x++;
		}
		y++;
	}
}
