/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray_casting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:32:28 by omeslall          #+#    #+#             */
/*   Updated: 2022/11/03 17:33:01 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
	{
		angle = (2 * PI) + angle;
	}
	return (angle);
}

void	init_t_ray(t_ray **ray, float ray_angle)
{
	(*ray)->ray_angle = fmod(2 * PI + fmod(ray_angle, 2 * PI), 2 * PI);
	(*ray)->h_wallhit_x = 0;
	(*ray)->h_wallhit_y = 0;
	(*ray)->v_wallhit_x = 0;
	(*ray)->v_wallhit_y = 0;
	(*ray)->distance = 0;
	if ((*ray)->ray_angle > 0 && (*ray)->ray_angle < PI)
		(*ray)->if_down = 1;
	else
		(*ray)->if_down = 0;
	(*ray)->if_up = !(*ray)->if_down;
	if ((*ray)->ray_angle < 0.5 * PI || (*ray)->ray_angle > 1.5 * PI)
		(*ray)->if_r = 1;
	else
		(*ray)->if_r = 0;
	(*ray)->if_l = !(*ray)->if_r;
	(*ray)->is_vert = false;
	(*ray)->is_horz = false;
}
