/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray_casting_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:50:49 by omeslall          #+#    #+#             */
/*   Updated: 2022/11/17 00:59:42 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vert	*init_t_vert(void)
{
	t_vert	*vert;

	vert = malloc(sizeof(t_vert));
	vert->xintercept = 0;
	vert->yintercept = 0;
	vert->v_xstep = 0;
	vert->v_ystep = 0;
	vert->vert_distance = 0;
	vert->found_vert_wallhit = false;
	return (vert);
}

void	calculate_ver_step(t_vert *vert, t_data *data, t_ray *ray)
{
	vert->xintercept = ((int)((data->player->x / TILE_SIZE))) * TILE_SIZE;
	if (ray->if_r)
		vert->xintercept += TILE_SIZE;
	vert->yintercept = (data->player->y + \
	(vert->xintercept - data->player->x) * tan(ray->ray_angle));
	vert->v_xstep = TILE_SIZE;
	if (ray->if_l)
		vert->v_xstep *= -1;
	vert->v_ystep = TILE_SIZE * tan(ray->ray_angle);
	if (ray->if_up && vert->v_ystep > 0)
		vert->v_ystep *= -1;
	if (ray->if_down && vert->v_ystep < 0)
		vert->v_ystep *= -1;
	if (ray->if_l)
		vert->xintercept--;
}
