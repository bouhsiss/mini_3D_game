/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray_Casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:23:49 by omeslall          #+#    #+#             */
/*   Updated: 2022/11/17 00:51:32 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	v_wall_hit(t_vert *vert, t_data *data, t_ray *ray)
{
	vert->found_vert_wallhit = true;
	ray->v_wallhit_x = vert->xintercept;
	ray->v_wallhit_y = vert->yintercept;
	if (ray->if_l)
		ray->v_wallhit_x++;
	vert->vert_distance = hypotf(ray->v_wallhit_x - data->player->x \
	, ray->v_wallhit_y - data->player->y);
}

t_distance	*vert_distance(t_ray *ray, t_data *data, t_distance *distance)
{
	t_vert	*vert;

	vert = init_t_vert();
	calculate_ver_step(vert, data, ray);
	while (vert->xintercept >= 0 && vert->xintercept \
	<= (data->mapdisplay->columns_nbr * TILE_SIZE) && vert->yintercept \
	>= 0 && vert->yintercept <= (data->mapdisplay->rows_nbr * TILE_SIZE))
	{
		if (has_wall_at(vert->xintercept, vert->yintercept, data))
		{
			v_wall_hit(vert, data, ray);
			break ;
		}
		else
		{
			vert->xintercept += vert->v_xstep;
			vert->yintercept += vert->v_ystep;
		}
	}
	if (vert->found_vert_wallhit)
		distance->vert_distance = vert->vert_distance;
	free(vert);
	return (distance);
}

t_distance	*init_t_distance(void)
{
	t_distance	*distance;

	distance = malloc(sizeof(t_distance));
	distance->horz_distance = INT64_MAX;
	distance->vert_distance = INT64_MAX;
	return (distance);
}

void	intercept(t_data *data)
{
	t_distance	*distance;

	distance = NULL;
	distance = init_t_distance();
	distance = horz_distance(data->mapdisplay->ray, data, distance);
	distance = vert_distance(data->mapdisplay->ray, data, distance);
	if (distance->vert_distance < distance->horz_distance)
	{
		data->mapdisplay->ray->distance = distance->vert_distance;
		data->mapdisplay->ray->is_vert = true;
	}
	else
	{
		data->mapdisplay->ray->distance = distance->horz_distance;
		data->mapdisplay->ray->is_horz = true;
	}
	free(distance);
}

void	cast_rays(t_data *data)
{
	int		i;
	float	dtpp;

	i = -1;
	dtpp = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	while (++i < WINDOW_WIDTH)
	{
		data->mapdisplay->ray->ray_angle = data->player->initial_angle \
		+ atan((i - 0.5 * WINDOW_WIDTH) / dtpp);
		init_t_ray(&data->mapdisplay->ray, data->mapdisplay->ray->ray_angle);
		intercept(data);
		render_wall(data, i, data->mapdisplay->ray, dtpp);
	}
	draw_minimap(&data);
}
