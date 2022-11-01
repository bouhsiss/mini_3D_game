/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:27:47 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/31 16:27:48 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	up_or_down(float angle, int *var_y)
{
	if (angle >= 0 && angle <= PI)
	{
		*var_y = 1;
		return (RESOLUTION);
	}
	else
	{
		*var_y = -1;
		return (-1);
	}
}

int	right_or_left(float ray_angle, int *var_x)
{
	if (ray_angle > PI / 2 && ray_angle < (3 * PI) / 2)
	{
		*var_x = -1;
		return (-1);
	}
	else
	{
		*var_x = 1;
		return (RESOLUTION);
	}
}

float	cos_or_sin(float adjacent, float opposite, float angle)
{
	if (sin(angle) > 0 && sin(angle) < 0.0001)
		return (adjacent / cos(angle));
	else if (cos(angle) > 0 && cos(angle) < 0.0001)
		return (opposite / sin(angle));
	else
		return (opposite / sin(angle));
}

float	find_h_intersection(t_data **data, float ray_angle)
{
	float	inter_x;
	float	inter_y;
	float	delta_x;
	float	delta_y;
	int		var_y;

	inter_y = (*data)->player->y / RESOLUTION;
	inter_y = (int)inter_y * RESOLUTION + up_or_down(ray_angle, &var_y);
	inter_x = (*data)->player->x + (inter_y - (*data)->player->y) / \
		tan(ray_angle);
	delta_y = var_y * RESOLUTION;
	delta_x = RESOLUTION / tan(ray_angle);
	while (abs((int)inter_y / RESOLUTION) >= 0 && abs((int)inter_y / \
		RESOLUTION) < (*data)->MapDisplay->NbrOfRows && abs((int)inter_x / \
		RESOLUTION) >= 0 && abs((int)inter_x / RESOLUTION) <= \
		ft_strlen(((*data)->MapDisplay->map[abs((int)inter_y / RESOLUTION)])))
	{
		if (check_is_wall(data, inter_x, inter_y) == true)
			return (cos_or_sin(fabs(inter_x - (*data)->player->x), \
			fabs(inter_y - (*data)->player->y), ray_angle));
		inter_x += (var_y) * delta_x;
		inter_y += delta_y;
	}
	return (cos_or_sin(fabs(inter_x - (*data)->player->x), fabs(inter_y - \
		(*data)->player->y), ray_angle));
}

float	find_v_intersection(t_data **data, float ray_angle)
{
	float	inter_x;
	float	inter_y;
	float	delta_x;
	float	delta_y;
	int		var_x;

	inter_x = (*data)->player->x / RESOLUTION;
	inter_x = (int)inter_x * RESOLUTION + right_or_left(ray_angle, &var_x);
	inter_y = (*data)->player->y + (inter_x - (*data)->player->x) * \
		tan(ray_angle);
	delta_x = var_x * RESOLUTION;
	delta_y = var_x * RESOLUTION * tan(ray_angle);
	while (abs((int)inter_y / RESOLUTION) >= 0 && abs((int)inter_y / \
	RESOLUTION) < (*data)->MapDisplay->NbrOfRows && abs((int)inter_x / \
	RESOLUTION) >= 0 && abs((int)inter_x / RESOLUTION) <= \
	ft_strlen(((*data)->MapDisplay->map[abs((int)inter_y / RESOLUTION)])))
	{
		if (check_is_wall(data, inter_x, inter_y) == true)
			return (cos_or_sin(fabs(inter_x - (*data)->player->x), \
			fabs(inter_y - (*data)->player->y), ray_angle));
		inter_x += delta_x;
		inter_y += delta_y;
	}
	return (cos_or_sin(fabs(inter_x - (*data)->player->x), \
	fabs(inter_y - (*data)->player->y), ray_angle));
}

float	cast_a_one_single_lonely_ray(t_data **data, float ray_angle)
{
	float	h_intersection;
	float	v_intersection;

	h_intersection = fabsf(find_h_intersection(data, ray_angle));
	v_intersection = fabsf(find_v_intersection(data, ray_angle));
	if (h_intersection < v_intersection)
	{
		drawline(data, cos(ray_angle) * (h_intersection), sin(ray_angle) * \
		h_intersection, 0xB7CFFF);
		return (h_intersection);
	}
	else
	{
		drawline(data, cos(ray_angle) * (v_intersection), sin(ray_angle) * \
		v_intersection, 0xB7CFFF);
		return (v_intersection);
	}
}

float	sanitize(float angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
	{
		angle = angle + (2 * PI);
	}
	return (angle);
}

void	cast_rays(t_data **data)
{
	int		num_rays;
	float	ray_angle;
	int		i;

	i = 0;
	num_rays = (((*data)->MapDisplay->NbrOfColumns * RESOLUTION) / \
		RAY_STRIP_WIDTH) * 10;
	ray_angle = sanitize((*data)->player->initialAngle) - (FOV / 2);
	(*data)->rays = malloc(sizeof(int) * (num_rays + 1));
	while (i < num_rays)
	{
		(*data)->rays[i] = cast_a_one_single_lonely_ray(data, ray_angle);
		ray_angle += FOV / num_rays;
		ray_angle = sanitize(ray_angle);
		i++;
	}
	(*data)->rays[i] = 0;
}
