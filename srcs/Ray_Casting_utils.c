/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rayc_Casting_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:48:00 by omeslall          #+#    #+#             */
/*   Updated: 2022/11/17 00:51:08 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	has_wall_at(float x, float y, t_data *data)
{
	int	grid_index_x;
	int	grid_index_y;

	grid_index_y = (int)(y / TILE_SIZE);
	if (grid_index_y >= data->mapdisplay->rows_nbr || grid_index_y < 0)
		return (false);
	grid_index_x = (int)(x / TILE_SIZE);
	if (grid_index_x > ft_strlen(data->mapdisplay->map[grid_index_y]) - 1 || \
		grid_index_x < 0)
		return (false);
	return (!is_valid_char(data->mapdisplay->map[grid_index_y][grid_index_x]));
}

t_horz	*init_t_horz(void)
{
	t_horz	*horz;

	horz = malloc(sizeof(t_horz));
	horz->xintercept = 0;
	horz->yintercept = 0;
	horz->h_xstep = 0;
	horz->h_ystep = 0;
	horz->horz_distance = 0;
	horz->found_horz_wallhit = false;
	return (horz);
}

void	calculate_horz_step(t_horz *horz, t_data *data, t_ray *ray)
{
	horz->yintercept = ((int)((data->player->y / TILE_SIZE))) * TILE_SIZE;
	if (ray->if_down)
		horz->yintercept += TILE_SIZE;
	horz->xintercept = (data->player->x + (horz->yintercept - data->player->y) \
	/ tan(ray->ray_angle));
	horz->h_ystep = TILE_SIZE;
	if (ray->if_up)
		horz->h_ystep *= -1;
	horz->h_xstep = TILE_SIZE / tan(ray->ray_angle);
	if (ray->if_l && horz->h_xstep > 0)
		horz->h_xstep *= -1;
	if (ray->if_r && horz->h_xstep < 0)
		horz->h_xstep *= -1;
	if (ray->if_up)
		horz->yintercept--;
}

void	h_wall_hit(t_horz *horz, t_data *data, t_ray *ray)
{
	horz->found_horz_wallhit = true;
	ray->h_wallhit_x = horz->xintercept;
	ray->h_wallhit_y = horz->yintercept;
	if (ray->if_up)
		ray->h_wallhit_y++;
	horz->horz_distance = hypotf(ray->h_wallhit_x - data->player->x, \
	ray->h_wallhit_y - data->player->y);
}

t_distance	*horz_distance(t_ray *ray, t_data *data, t_distance *distance)
{
	t_horz	*horz;
	t_map	*map;

	map = data->mapdisplay;
	horz = init_t_horz();
	calculate_horz_step(horz, data, ray);
	while (horz->xintercept >= 0 && horz->xintercept <= (map->columns_nbr * \
	TILE_SIZE) && horz->yintercept >= 0 && horz->yintercept <= \
	(map->rows_nbr * TILE_SIZE))
	{
		if (has_wall_at(horz->xintercept, horz->yintercept, data))
		{
			h_wall_hit(horz, data, ray);
			break ;
		}
		else
		{
			horz->xintercept += horz->h_xstep;
			horz->yintercept += horz->h_ystep;
		}
	}
	if (horz->found_horz_wallhit)
		distance->horz_distance = horz->horz_distance;
	free (horz);
	return (distance);
}
