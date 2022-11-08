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
		return (MINI_MAP_TILE_SIZE);
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
		return (MINI_MAP_TILE_SIZE);
	}
}

bool hit_wall(t_data **data, float next_x, float next_y, float ray_angle)
{
	int i;
	int j;
	int right_left;
	int up_down;
	char **map;

	right_or_left(ray_angle, &right_left);
	up_or_down(ray_angle, &up_down);
	map = (*data)->MapDisplay->map;
	i = next_x / MINI_MAP_TILE_SIZE;
	j = next_y / MINI_MAP_TILE_SIZE;
	if(map[j][i] == '1')
	{
		return(true);
	}
	else if( (i < ft_strlen(map[j-up_down]))&& (j-up_down) < (*data)->MapDisplay->NbrOfRows && (i-right_left) < ft_strlen(map[j]))
	{
		if((map[j-up_down][i] == '1' && map[j][i-right_left] == '1'))
		{
			return(true);
		}
	}
	else
	{
		return(false);
	}
	return(false);
}


float	find_h_intersection(t_data **data, float ray_angle)
{
	float	inter_x;
	float	inter_y;
	float	delta_x;
	float	delta_y;
	int		var_y;

	inter_y = (*data)->player->y / MINI_MAP_TILE_SIZE;
	inter_y = (int)inter_y * MINI_MAP_TILE_SIZE + up_or_down(ray_angle, &var_y);
	inter_x = (*data)->player->x + (inter_y - (*data)->player->y) / \
		tan(ray_angle);
	delta_y = var_y * MINI_MAP_TILE_SIZE;
	delta_x = var_y * (MINI_MAP_TILE_SIZE / tan(ray_angle));
	while ((int)inter_y / MINI_MAP_TILE_SIZE >= 0 && (int)inter_y / \
		MINI_MAP_TILE_SIZE < (*data)->MapDisplay->NbrOfRows && (int)inter_x / \
		MINI_MAP_TILE_SIZE >= 0 && (int)inter_x / MINI_MAP_TILE_SIZE <= \
		ft_strlen(((*data)->MapDisplay->map[(int)inter_y / MINI_MAP_TILE_SIZE])))
	{
		if(hit_wall(data, inter_x, inter_y, ray_angle) == true)
			return(hypot(fabs(inter_x - (*data)->player->x), fabs(inter_y - (*data)->player->y)));
		inter_x += delta_x;
		inter_y += delta_y;
	}
	return (hypot(fabs(inter_x - (*data)->player->x), fabs(inter_y - (*data)->player->y)));
}

float	find_v_intersection(t_data **data, float ray_angle)
{
	float	inter_x;
	float	inter_y;                                                        
	float	delta_x;
	float	delta_y;
	int		var_x;

	inter_x = (*data)->player->x / MINI_MAP_TILE_SIZE;
	inter_x = (int)inter_x * MINI_MAP_TILE_SIZE + right_or_left(ray_angle, &var_x);
	inter_y = (*data)->player->y + (inter_x - (*data)->player->x) * \
		tan(ray_angle);
	delta_x = var_x * MINI_MAP_TILE_SIZE;
	delta_y = var_x * MINI_MAP_TILE_SIZE * tan(ray_angle);
	while ((int)inter_y / MINI_MAP_TILE_SIZE >= 0 && (int)inter_y / \
		MINI_MAP_TILE_SIZE < (*data)->MapDisplay->NbrOfRows && (int)inter_x / \
		MINI_MAP_TILE_SIZE >= 0 && (int)inter_x / MINI_MAP_TILE_SIZE <= \
		ft_strlen(((*data)->MapDisplay->map[(int)inter_y / MINI_MAP_TILE_SIZE])))
	{
		if(hit_wall(data, inter_x, inter_y, ray_angle) == true)
			return(hypot(fabs(inter_x - (*data)->player->x), fabs(inter_y - (*data)->player->y)));
		inter_x += delta_x;
		inter_y += delta_y;
	}
	return (hypot(fabs(inter_x - (*data)->player->x), fabs(inter_y - (*data)->player->y)));
}

float	cast_a_one_single_lonely_ray(t_data **data, float ray_angle)
{
	float	h_intersection;
	float	v_intersection;

	h_intersection = find_h_intersection(data, ray_angle);
	v_intersection = find_v_intersection(data, ray_angle);
	if (h_intersection <= v_intersection)
	{
		// drawline(data, cos(ray_angle) * (h_intersection), sin(ray_angle) * \
		// h_intersection, 0xB7CFFF);
		printf("h x %f y %f\n",  cos(ray_angle) * (h_intersection), sin(ray_angle) * h_intersection);
		return (h_intersection);
	}
	else
	{
		// drawline(data, cos(ray_angle) * (v_intersection), sin(ray_angle) * \
		// v_intersection, 0xB7CFFF);
		printf("v x %f y %f\n",  cos(ray_angle) * (v_intersection), sin(ray_angle) * v_intersection);
		return (v_intersection);
	}
}
