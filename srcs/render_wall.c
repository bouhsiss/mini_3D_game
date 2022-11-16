/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:12:29 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/16 21:12:32 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	adjust_length(int wall_strip_height, int *end)
{
	int	start;

	start = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
	if (start < 0)
		start = 0;
	*end = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
	if (*end > WINDOW_HEIGHT)
		*end = WINDOW_HEIGHT;
	return (start);
}

t_img	*north_or_south(t_data *data, float ray_angle)
{
	if (ray_angle >= 0 && ray_angle <= PI)
		return (data->mapdisplay->text_imgs->south);
	else
		return (data->mapdisplay->text_imgs->north);
}

t_img	*east_or_west(t_data *data, float ray_angle)
{
	if (ray_angle >= PI / 2 && ray_angle <= (3 * PI) / 2)
		return (data->mapdisplay->text_imgs->east);
	else
		return (data->mapdisplay->text_imgs->west);
}

void	map_texture_to_wall(t_data *data, int x, int y, int offset_y)
{
	int				offset_x;
	t_img			*texture;
	unsigned int	color;
	t_ray			*ray;

	ray = data->mapdisplay->ray;
	ray->ray_angle = fmod(2 * PI + fmod(ray->ray_angle, 2 * PI), 2 * PI);
	if (ray->is_vert == true)
	{
		offset_x = (int)ray->v_wallhit_y % TILE_SIZE;
		texture = east_or_west(data, ray->ray_angle);
		color = my_mlx_pixel_get(texture, offset_x, offset_y);
	}
	else
	{
		offset_x = (int)ray->h_wallhit_x % TILE_SIZE;
		texture = north_or_south(data, ray->ray_angle);
		color = my_mlx_pixel_get(texture, offset_x, offset_y);
	}
	my_mlx_pixel_put(data->win->win_img, x, y, color);
}

void	render_wall(t_data *data, int x, t_ray *ray, int dtpp)
{
	int		wall_strip_height;
	float	ray_length;
	int		y;
	int		end;
	int		offset_y;

	ray_length = ray->distance * cos(ray->ray_angle - \
	data->player->initial_angle);
	wall_strip_height = (TILE_SIZE / (ray_length) * dtpp);
	y = adjust_length(wall_strip_height, &end);
	while (y < end)
	{
		offset_y = (y + (wall_strip_height / 2) - 0.5 * WINDOW_HEIGHT)
			* ((float)TILE_SIZE / wall_strip_height);
		map_texture_to_wall(data, x, y, offset_y);
		y++;
	}
}
